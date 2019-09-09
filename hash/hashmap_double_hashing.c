#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "hash_func.h"
#include "hashmap_impl.h"

#define HASHMAP_INSTANCE(_map) hashmap map = (hashmap)(_map)
#define HASHMAP_INIT_CAPACITY (16U)

typedef struct _hashmap *hashmap;
typedef struct _bucket *bucket;
typedef uint (*probe)(hashmap, any_t);

struct _bucket {
    any_t key;
    any_t value;
    int   is_tomb;
};

struct _hashmap {
    uint          capacity;
    uint          size;
    bucket        buckets;
    probe         probing_func;
    HashFunc      hash_func;
    HashEqualFunc key_equal_func;
};

static uint linear_probing(hashmap map, any_t index)
{
    return (*(uint *)index+1) % map->capacity;
}

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

static void hashmap_resize(hashmap map, uint ratio)
{
    uint capacity_old = map->capacity;
    uint capacity_new = capacity_old * ratio;
    map->capacity = capacity_new;
    void *temp = realloc(map->buckets, sizeof(struct _bucket) * capacity_new);
    if (temp)
        map->buckets = (bucket)temp;
    
    for (int i = capacity_old; i < capacity_new; i++) {
        map->buckets[i].key     = NULL;
        map->buckets[i].value   = NULL;
        map->buckets[i].is_tomb = 0;
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
    while (try_lookup_to_bucket(&buckets[index], key, key_equal_func)) {
        index = map->probing_func(map, &index);
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

void *hashmap_double_hashing_create(HashFunc hash_func, HashEqualFunc key_equal_func)
{
    hashmap map = calloc(1, sizeof(struct _hashmap));
    if (!map)
        return NULL;
    
    map->size           = 0;
    map->capacity       = HASHMAP_INIT_CAPACITY;
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

void hashmap_double_hashing_destroy(hashmap_t _map)
{
    if (!_map)
        return;

    HASHMAP_INSTANCE(_map);
    free(map->buckets);
    free(map);
}

any_t hashmap_double_hashing_find(hashmap_t _map, any_t key)
{
    if (!_map || !key)
        return NULL;
    
    HASHMAP_INSTANCE(_map);
    uint index = hash_key_to_index(map, key);
    uint start = index;
    HashEqualFunc key_equal_func = map->key_equal_func;
    bucket buckets = map->buckets;
    while (try_lookup_to_bucket(&buckets[index], key, key_equal_func) == HASHMAP_MISS) {
        index = map->probing_func(map, &index);
        if (index == start)
            return NULL;
    }
    return buckets[index].value;
}

int hashmap_double_hashing_has_key(hashmap_t _map, any_t key)
{
    if (!_map || !key)
        return HASHMAP_MISS;
    
    HASHMAP_INSTANCE(_map);
    uint index = hash_key_to_index(map, key);
    uint start = index;
    HashEqualFunc key_equal_func = map->key_equal_func;
    bucket buckets = map->buckets;
    while (try_lookup_to_bucket(&buckets[index], key, key_equal_func) == HASHMAP_MISS) {
        index = map->probing_func(map, &index);
        if (index == start)
            return HASHMAP_MISS;
    }
    return HASHMAP_HIT;
}

uint hashmap_double_hashing_size(hashmap_t _map)
{
    HASHMAP_INSTANCE(_map);
    return map->size;
}

void hashmap_double_hashing_iterate(hashmap_t _map, PFany fptr, any_t args)
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

void hashmap_double_hashing_insert(hashmap_t _map, any_t key, any_t value)
{
    if (!_map || !key)
        return;
    
    HASHMAP_INSTANCE(_map);
    if (map->size == map->capacity)
        hashmap_resize(map, 2);

    uint index = hash_key_to_index(map, key);
    while (try_insert_to_bucket(&map->buckets[index], key, value)) {
        index = map->probing_func(map, &index);
    }
    map->size++;
}

void hashmap_double_hashing_remove(hashmap_t _map, any_t key)
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

void hashmap_double_hashing_dump(hashmap_t _map, printFunc fptr)
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