#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "hash_func.h"
#include "hashmap_impl.h"

#define HASHMAP_INSTANCE(_ptr) hashmap map = (hashmap)(_ptr)
#define HASHMAP_MIN_SHIFT     (3)
#define HASHMAP_RESIZE_FACTOR (5)

typedef struct _entry *entry;
struct _entry {
    entry next;
    any_t key;
    any_t value;
};

typedef struct _hashmap *hashmap;
struct _hashmap {
    uint          capacity;
    uint          size;
    int           mod;
    int           shifted;
    int           resize_factor;
    entry        *entries;
    HashFunc      hash_func;
    HashEqualFunc key_equal_func;
};

static entry entry_create(void)
{
    entry e = calloc(1, sizeof(struct _entry));
    if (!e)
        return NULL;
    
    e->next   = NULL;
    e->key    = NULL;
    e->value  = NULL;

    return e;
}

static void hashmap_init(hashmap map)
{
    map->entries = calloc(map->capacity, sizeof(entry));
    if (!map->entries)
        return;
    
    for (int i = 0; i < map->capacity; i++)
        map->entries[i] = entry_create();
}

static void entry_destroy(entry e)
{
    if (!e)
        return;
    
    e->key   = NULL;
    e->value = NULL;
    e->next  = NULL;
    free(e);
}

static void entry_iterate(entry e, PFany fptr, any_t args)
{
    entry cur = e;
    while (cur) {
        (*fptr)(cur, args);
        cur = cur->next;
    }
}

static void entry_iterate_key(entry e, PFany fptr, any_t args)
{
    entry cur = e;
    while (cur) {
        (*fptr)(cur->key, args);
        cur = cur->next;
    }
}

static void entry_iterate_value(entry e, PFany fptr, any_t args)
{
    entry cur = e;
    while (cur) {
        (*fptr)(cur->value, args);
        cur = cur->next;
    }
}

static void entry_iterate_destroy(entry e)
{
    if (!e)
        return;

    entry cur  = e;
    entry next = NULL;
    while (cur) {
        next = cur->next;
        entry_destroy(cur);
        cur = next;
    }
}

static any_t entry_look_up(entry e, any_t key, HashEqualFunc key_equal_func, entry *last, int *len)
{
    if (!e->key)
        return NULL;

    (int *)len;

    entry cur = e;
    int result = HASHMAP_MISS;
    while (cur) {
        *len = *len + 1;
        result = (*key_equal_func)(cur->key, key);
        if (result == HASHMAP_HIT) {
            return cur;
        }
        *last = cur;
        cur  = cur->next;
    }
    return NULL;
}

static inline uint hash_key(HashFunc hash_func, any_t key)
{
    return (*hash_func)(key);
}

static inline uint hash_to_index(int mod, uint hash)
{
    return (hash * 11) % mod;
}

static inline uint hash_key_to_index(hashmap map, any_t key)
{
    uint hash = hash_key(map->hash_func, key);
    return hash_to_index(map->mod, hash);
}

static void hashmap_destroy_all_entries(hashmap map)
{

}

static void insert_entry_to_entries(entry e, entry *entries, uint index)
{
    entry head = entries[index];

    if (!head->key) {
        head->key   = e->key;
        head->value = e->value;
        return;
    }

    entry node = head;
    while (node->next)
        node = node->next;
    
    node->next = entry_create();
    node = node->next;
    node->key   = e->key;
    node->value = e->value;
}

static int hashmap_rehash_entry(hashmap map, entry e, entry *entries)
{
    if (!e || !e->key)
        return HASHMAP_MISS;
    
    uint index = hash_key_to_index(map, e->key);
    insert_entry_to_entries(e, entries, index);
    return HASHMAP_HIT;
}

static int hashmap_rehash_entry_wrapper(void *_entry, void *_args)
{
    struct entry_params {
        void  *_hashmap;
        entry *_entries;
    };

    struct entry_params *param = (struct entry_params *)_args;
    hashmap map    = (hashmap)param->_hashmap;
    entry *entries = (entry *)param->_entries;
    entry e        = (entry)_entry;
    return hashmap_rehash_entry(map, e, entries);
}

static void hashmap_resize_bigger(hashmap map)
{
    uint capacity_old = map->capacity;
    uint capacity_new = capacity_old << 1;

    /* create a new table for entries */
    entry *entries = calloc(capacity_new, sizeof(entry));
    for (int i = 0; i < capacity_new; i++)
        entries[i] = entry_create();

    /* update hashmap */
    map->capacity = capacity_new;
    map->shifted  = map->shifted + 1;
    map->mod      = prime_mode[map->shifted];

    /* define struct for iterate function */
    struct entry_params {
        void  *_hashmap;
        entry *_entries;
    };
    struct entry_params args = {
        ._hashmap = (void *)map,
        ._entries = entries,
    };

    /* iterate old entries in hashmap and reshash them to new entries */
    for (int i = 0; i < capacity_old; i++)
        entry_iterate(map->entries[i], hashmap_rehash_entry_wrapper, (any_t)&args);

    /* cleanup old entries and assign new entries to hashmap instance */
    hashmap_destroy_all_entries(map);
    map->entries = entries;
}

void *hashmap_chaining_create(HashFunc hash_func, HashEqualFunc key_equal_func)
{
    hashmap map = calloc(1, sizeof(struct _hashmap));
    if (!map)
        return NULL;
    
    map->size           = 0;
    map->capacity       = 1 << HASHMAP_MIN_SHIFT;
    map->shifted        = HASHMAP_MIN_SHIFT;
    map->resize_factor  = HASHMAP_RESIZE_FACTOR;
    map->mod            = prime_mode[HASHMAP_MIN_SHIFT];
    map->hash_func      = hash_func ? hash_func : hash_direct;
    map->key_equal_func = key_equal_func;
    hashmap_init(map);

    return map;
}

void hashmap_chaining_destroy(hashmap_t _map)
{
    HASHMAP_INSTANCE(_map);
    uint capacity = map->capacity;
    for (int i = 0; i < capacity; i++)
        entry_iterate_destroy(map->entries[i]);
    free(map->entries);
    free(map);
}

any_t hashmap_chaining_find(hashmap_t _map, any_t key)
{
    if (!key || !_map)
        return NULL;
    
    HASHMAP_INSTANCE(_map);
    uint  index  = hash_key_to_index(map, key);
    entry last   = NULL;
    int   length = 0;
    entry e = entry_look_up(map->entries[index], key, map->key_equal_func, &last, &length);
    return e ? e->value : NULL;
}

int hashmap_chaining_has_key(hashmap_t _map, any_t key)
{
    return hashmap_chaining_find(_map, key)? 1 : 0;
}

int hashmap_chaining_size(hashmap_t _map)
{
    HASHMAP_INSTANCE(_map);
    return map->size;
}

void hashmap_chaining_iterate(hashmap_t _map, PFany fptr, any_t args)
{
    HASHMAP_INSTANCE(_map);
    uint capacity = map->capacity;
    for (int i = 0; i < capacity; i++)
        entry_iterate_value(map->entries[i], fptr, args);
}

void hashmap_chaining_insert(hashmap_t _map, any_t key, any_t value)
{
    if (!_map || !key)
        return;

    HASHMAP_INSTANCE(_map);
    uint index = hash_key_to_index(map, key);

    if (!map->entries[index]->key) {
        map->entries[index]->key   = key;
        map->entries[index]->value = value;
        map->size++;
        return;
    }

    entry last   = NULL;
    int   length = 0;
    entry e = entry_look_up(map->entries[index], key, map->key_equal_func, &last, &length);

    /* insert this <k,v> to hashmap if it is not exist in current hashmap */
    if (!e) {
        if (length >= map->resize_factor)
            hashmap_resize_bigger(map);
        last->next = entry_create();
        e          = last->next;
        e->next    = NULL;
        e->key     = key;
        e->value   = value;
        map->size++;
    }
}

void hashmap_chaining_remove(hashmap_t _map, any_t key)
{
    HASHMAP_INSTANCE(_map);
    uint index = hash_key_to_index(map, key);
    entry last = NULL;
    int   len  = 0;
    entry e = entry_look_up(map->entries[index], key, map->key_equal_func, &last, &len);
    if (!e)
        return;
    
    entry next = e->next;
    entry_destroy(e);
    if (last)
        last->next = next;
    map->size--;
}

void hashmap_chaining_dump(hashmap_t _map, printFunc print_fn)
{
    HASHMAP_INSTANCE(_map);
    uint capacity = map->capacity;
    for (int i = 0; i < capacity; i++) {
        printf("#%03d: [", i);
        if (!map->entries[i]->key) {
            printf(" (nil) ]\n");
            continue;
        }
        for (entry e = map->entries[i]; e != NULL; e = e->next) {
            if (e->key && e->value)
                (*print_fn)(e->value);
        }
        printf(" ]\n");
    }
}