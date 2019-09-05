#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "hash_func.h"
#include "hashmap_impl.h"

#define HASHMAP_INSTANCE(_ptr) hashmap map = (hashmap)(_ptr)
#define HASHMAP_MIN_SHIFT     (3)
#define HASHMAP_RESIZE_FACTOR (3)

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
}

static entry hashmap_init(hashmap map)
{
    map->entries = calloc(map->capacity, sizeof(entry));
    if (!map->entries)
        return NULL;
    
    for (int i = 0; i < map->capacity; i++)
        map->entries[i] = entry_create();
}

static void entry_iterate(entry e, PFany fptr, any_t args)
{
    entry cur = e;
    while (cur) {
        (*fptr)(cur->value, args);
        cur = cur->next;
    }
}

static any_t entry_look_up(entry e, any_t key, HashEqualFunc key_equal_func, entry *last, int *len)
{
    if (!e->key)
        return NULL;

    entry cur = e;
    int result = HASHMAP_MISS;
    while (cur) {
        *len++;
        result = (*key_equal_func)(cur->key, key);
        if (result == HASHMAP_HIT) {
            return cur;
        }
        *last = cur;
        cur  = cur->next;
    }
    return NULL;
}

static uint hash_to_index(hashmap map, uint hash)
{
    return (hash * 11) % map->mod;
}

void *hashmap_chaining_create(HashFunc hash_func, HashEqualFunc key_equal_func)
{
    hashmap map = calloc(1, sizeof(struct _hashmap));
    if (!map)
        return NULL;
    
    map->size           = 0;
    map->capacity       = 1 << HASHMAP_MIN_SHIFT;
    map->shifted        = HASHMAP_MIN_SHIFT;
    map->mod            = prime_mode[HASHMAP_MIN_SHIFT];
    map->hash_func      = hash_func ? hash_func : hash_direct;
    map->key_equal_func = key_equal_func;

    return map;
}

/* TODO */
void hashmap_chaining_destroy(hashmap_t _map)
{
    HASHMAP_INSTANCE(_map);
    uint capacity = map->capacity;
    for (int i = 0; i < capacity; i++) {
        map->entries[i];
    }
}

any_t hashmap_chaining_find(hashmap_t _map, any_t key)
{
    if (!key || !_map)
        return NULL;
    
    HASHMAP_INSTANCE(_map);
    uint hash  = map->hash_func(key);
    uint index = hash_to_index(map, hash);
    entry last = NULL;
    int length = 0;
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
        entry_iterate(map->entries[i], fptr, args);
}

void hashmap_chaining_insert(hashmap_t _map, any_t key, any_t value)
{
    if (!_map || !key)
        return;

    HASHMAP_INSTANCE(_map);
    uint hash  = map->hash_func(key);
    uint index = hash_to_index(map, hash);

    if (!map->entries[index]->key) {
        map->entries[index]->key   = key;
        map->entries[index]->value = value;
        return;
    }

    entry last = NULL;
    int length = 0;
    entry e = entry_look_up(map->entries[index], key, map->key_equal_func, &last, &length);
    if (!e) {
        if (length < HASHMAP_RESIZE_FACTOR) {
            last->next = entry_create();
            e          = last->next;
            e->next    = NULL;
            e->key     = key;
            e->value   = value;
        }
        else {
            uint old_capacity = map->capacity;
            uint new_capacity = old_capacity << 1;
            map->capacity = new_capacity;
            map->shifted  = map->shifted + 1;
            map->mod      = prime_mode[map->shifted];
            realloc(map->entries, map->capacity*sizeof(entry));
            for (int i = old_capacity; i < new_capacity; i++)
                map->entries[i] = entry_create();
        }
    }
}

void hashmap_chaining_remove(hashmap_t, any_t);