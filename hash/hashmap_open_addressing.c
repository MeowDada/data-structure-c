#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "hash_func.h"
#include "hashmap_impl.h"

#define HASHMAP_INSTANCE(_map) hashmap map = (hashmap)(_map)
#define HASHMAP_MIN_SHIFT (4)

typedef struct _hashmap   *hashmap;
typedef struct _bucket    *bucket;
typedef struct _prob_args *prob_args;
typedef uint (*probe)(hashmap, prob_args);

struct _bucket {
    any_t key;
    any_t value;
    int   is_tomb;
};

struct _hashmap {
    uint          capacity;
    uint          size;
    int           shifted;
    int           mod;
    bucket        buckets;
    probe         probing_func;
    HashFunc      hash_func;
    HashEqualFunc key_equal_func;
};

struct _prob_args {
    uint  index;      /* commonly used */
    uint  start;      /* commonly used */
    int   last;       /* used for quadratic probing */
    uint  count;      /* used for double hashing */
    any_t key;        /* used for double hashing */
};

static struct _prob_args g_prob_args = {
    .index = 0,
    .last  = 0,
    .start = 0,
    .count = 1,
    .key   = NULL,
};

static prob_args prob_args_create(uint index, any_t key)
{
    prob_args args = calloc(1, sizeof(struct _prob_args));
    args->index = index;
    args->start = index;
    args->last  = 0;
    args->count = 1;
    args->key   = key;

    return args;
}

static inline void prob_args_set(prob_args args, uint index, any_t key)
{
    args->index = index;
    args->start = index;
    args->key   = key;
}

static inline void prob_args_set_index(prob_args args, uint index)
{
    args->index = index;
}

static inline void prob_args_reset(prob_args args)
{
    args->index = 0;
    args->start = 0;
    args->last  = 0;
    args->count = 1;
    args->key   = NULL;
}

static inline void prob_args_destroy(prob_args args)
{
    if (args)
        free(args);
}

static inline uint linear_probing(hashmap map, prob_args args)
{
    args->index = (args->index + 1) % map->capacity;
    return args->index;
}

static uint quadratic_probing(hashmap map, prob_args args)
{
    uint index  = args->index;
    int  last   = args->last;
    uint offset = 0;

    if (last < 0)
        offset = -1 * last * last;
    else
        offset = last * last;

    if (last == 0)
        args->last = 1;
    else if (last > 0)
        args->last *= -1;
    else
        args->last = (args->last*-1)+1;

    args->index = (index + offset) % map->capacity;
    return args->index;
}

static uint double_hashing(hashmap map, prob_args args)
{
    uint capacity = map->capacity;
    int index     = (int)args->index;
    int count     = args->count;
    int prime     = map->mod;
    int hash      = map->hash_func(args->key);

    uint ret = (hash + count * (1 + ((hash>>5)+1)) % (capacity-1)) % capacity;
    args->count += 1;
    args->index = ret;
    return ret;
}

static probe probing_func[] = {
    linear_probing,
    quadratic_probing,
    double_hashing,
};

static inline uint hash_key(HashFunc hash_func, any_t key)
{
    return (*hash_func)(key);
}

static inline uint hash_to_index(uint hash, int mod)
{
    return hash % mod;
}

static inline uint hash_key_to_index(hashmap map, any_t key)
{
    uint hash  = hash_key(map->hash_func, key);
    uint index = hash_to_index(hash, map->capacity);
    return index;
}

static void hashmap_rehash(hashmap map)
{
    /* create temp buckets and initialize it */
    uint capacity  = map->capacity;
    bucket buckets = map->buckets;
    bucket temp_bucket = calloc(capacity, sizeof(struct _bucket));
    if (!temp_bucket)
        return;

    for (int i = 0; i < capacity; i++) {
        temp_bucket[i].key     = NULL;
        temp_bucket[i].value   = NULL;
        temp_bucket[i].is_tomb = 0;
    }

    /* apply rehashing for each items in old buckets to temp buckets */
    for (int i = 0; i < capacity; i++) {
        if (buckets[i].key && !buckets[i].is_tomb) {
            any_t key   = buckets[i].key;
            any_t value = buckets[i].value;
            uint index  = hash_key_to_index(map, key);
            if (!temp_bucket[index].key) {
                temp_bucket[index].key   = key;
                temp_bucket[index].value = value;
                continue;
            }
            prob_args_reset(&g_prob_args);
            prob_args_set(&g_prob_args, index, key);
            while (1) {
                index = map->probing_func(map, &g_prob_args);
                if (!temp_bucket[index].key) {
                    temp_bucket[index].key   = key;
                    temp_bucket[index].value = value;
                    break;
                }
            }
        }
    }

    /* cleanup and assign new buckets to the hashmap instance */
    free(map->buckets);
    map->buckets = temp_bucket;
}

static void hashmap_resize_bigger(hashmap map)
{
    uint capacity_old = map->capacity;
    uint capacity_new = capacity_old << 1;
    map->capacity     = capacity_new;
    map->shifted      = map->shifted + 1;
    map->mod          = prime_mode[map->shifted];
    void *temp        = realloc(map->buckets, sizeof(struct _bucket) * capacity_new);
    if (temp)
        map->buckets = (bucket)temp;
    
    for (int i = capacity_old; i < capacity_new; i++) {
        map->buckets[i].key     = NULL;
        map->buckets[i].value   = NULL;
        map->buckets[i].is_tomb = 0;
    }

    /* rehashing all the value inside the hashmap if applying doulbe hashing method */
    if (map->probing_func == double_hashing) {
        hashmap_rehash(map);
    }
}

static int try_lookup_to_bucket(bucket b, any_t key, HashEqualFunc key_equal_func)
{
    if (!b->key || b->is_tomb)
        return -1;
    
    return (*key_equal_func)(b->key, key);
}

static int try_insert_to_bucket(bucket b, any_t key, any_t value)
{
    if (!b->key  || b->is_tomb) {
        b->key = key;
        b->value = value;
        b->is_tomb = 0;
        return 0;
    }
    return -1;
}

static bucket lookup_for_bucket(hashmap map, any_t key)
{
    uint index = hash_key_to_index(map, key);
    uint start = index;
    bucket buckets = map->buckets;
    HashEqualFunc key_equal_func = map->key_equal_func;
    prob_args_reset(&g_prob_args);
    prob_args_set(&g_prob_args, index, key);
    while (try_lookup_to_bucket(&buckets[index], key, key_equal_func)) {
        index = map->probing_func(map, &g_prob_args);
        if (index == start)
            return NULL;
    }
    return &buckets[index];
}

static void initialize_buckets(bucket buckets, uint capacity)
{
    for (int i = 0 ; i < capacity; i++) {
        buckets[i].is_tomb = 0;
        buckets[i].key     = NULL;
        buckets[i].value   = NULL;
    }
}

void *hashmap_open_addressing_create(HashFunc hash_func, HashEqualFunc key_equal_func)
{
    hashmap map = calloc(1, sizeof(struct _hashmap));
    if (!map)
        return NULL;
    
    map->size           = 0;
    map->capacity       = 1 << HASHMAP_MIN_SHIFT;
    map->shifted        = HASHMAP_MIN_SHIFT;
    map->mod            = prime_mode[map->shifted];
    map->hash_func      = hash_func ? hash_func : hash_direct;
    map->key_equal_func = key_equal_func;
    map->probing_func   = linear_probing;
    map->buckets        = calloc(map->capacity, sizeof(struct _bucket));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    initialize_buckets(map->buckets, map->capacity);

    return map;
}

void hashmap_open_addressing_destroy(hashmap_t _map)
{
    if (!_map)
        return;

    HASHMAP_INSTANCE(_map);
    free(map->buckets);
    free(map);
}

any_t hashmap_open_addressing_find(hashmap_t _map, any_t key)
{
    if (!_map || !key)
        return NULL;
    
    HASHMAP_INSTANCE(_map);
    uint index = hash_key_to_index(map, key);
    uint start = index;
    HashEqualFunc key_equal_func = map->key_equal_func;
    bucket buckets = map->buckets;
    prob_args_reset(&g_prob_args);
    prob_args_set(&g_prob_args, index, key);
    while (try_lookup_to_bucket(&buckets[index], key, key_equal_func) == HASHMAP_MISS) {
        index = map->probing_func(map, &g_prob_args);
        if (index == start)
            return NULL;
    }
    return buckets[index].value;
}

int hashmap_open_addressing_has_key(hashmap_t _map, any_t key)
{
    if (!_map || !key)
        return HASHMAP_MISS;
    
    HASHMAP_INSTANCE(_map);
    uint index = hash_key_to_index(map, key);
    uint start = index;
    HashEqualFunc key_equal_func = map->key_equal_func;
    bucket buckets = map->buckets;
    prob_args_reset(&g_prob_args);
    prob_args_set(&g_prob_args, index, key);
    while (try_lookup_to_bucket(&buckets[index], key, key_equal_func) == HASHMAP_MISS) {
        index = map->probing_func(map, &g_prob_args);
        if (index == start)
            return HASHMAP_MISS;
    }
    return HASHMAP_HIT;
}

uint hashmap_open_addressing_size(hashmap_t _map)
{
    HASHMAP_INSTANCE(_map);
    return map->size;
}

void hashmap_open_addressing_iterate(hashmap_t _map, PFany fptr, any_t args)
{
    if (!_map || !fptr)
        return;
    
    HASHMAP_INSTANCE(_map);
    uint capacity   = map->capacity;
    bucket buckets = map->buckets;
    for (int i = 0; i < capacity; i++) {
        if (buckets[i].key && !buckets[i].is_tomb)
            (*fptr)(buckets[i].value, args);
    }
}

void hashmap_open_addressing_insert(hashmap_t _map, any_t key, any_t value)
{
    if (!_map || !key)
        return;
    
    HASHMAP_INSTANCE(_map);
    if (map->size == map->capacity)
        hashmap_resize_bigger(map);

    uint index = hash_key_to_index(map, key);
    prob_args_reset(&g_prob_args);
    prob_args_set(&g_prob_args, index, key);
    while (try_insert_to_bucket(&map->buckets[index], key, value)) {
        index = map->probing_func(map, &g_prob_args);
    }
    map->size++;
}

void hashmap_open_addressing_remove(hashmap_t _map, any_t key)
{
    if (!_map || !key)
        return;
    
    HASHMAP_INSTANCE(_map);
    bucket b = lookup_for_bucket(map, key);
    if (b) {
        b->is_tomb = 1;
        map->size--;
    }
}

void hashmap_open_addressing_dump(hashmap_t _map, printFunc fptr)
{
    if (!_map || !fptr)
        return;
    
    HASHMAP_INSTANCE(_map);
    uint capacity = map->capacity;
    bucket buckets = map->buckets;
    for (int i = 0 ; i < capacity; i++) {
        printf("#%03d: [", i);
        if (buckets[i].key && !buckets[i].is_tomb)
            fptr(buckets[i].value);
        else
            printf(" (nil)");
        printf(" ]\n");
    }
}

void hashmap_open_addressing_probing(hashmap_t _map, int type)
{
    if (!_map)
        return;
    
    HASHMAP_INSTANCE(_map);
    map->probing_func = probing_func[type];
}