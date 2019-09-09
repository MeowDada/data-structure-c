#include <stdlib.h>
#include <memory.h>
#include "hashmap.h"
#include "hashmap_impl.h"
#include "hash_func.h"

#define HASHMAP_INSTANCE(_ptr) hashmap *map = (hashmap *)(_ptr)

typedef any_t hashmap_instance; 

typedef struct hashmap {
    hashmap_instance *instance;
    hashmap_impl     *impl;
} hashmap;

hashmap_t hashmap_create(int type, HashFunc hash_func, HashEqualFunc equal_func)
{
    hashmap *map = calloc(1, sizeof(hashmap));

    if (!map)
        return NULL;

    map->impl     = &hashmap_impl_table[type];
    map->instance = map->impl->_hashmap_create(hash_func, equal_func);

    if (!map->instance) {
        free(map);
        return NULL;
    }
    return map;
}

void hashmap_destroy(hashmap_t _map)
{
    HASHMAP_INSTANCE(_map);
    map->impl->_hashmap_destroy(map->instance);
    map->instance = NULL;
    free(_map);
}

any_t hashmap_find(hashmap_t _map, any_t key)
{
    HASHMAP_INSTANCE(_map);
    return map->impl->_hashmap_find(map->instance, key);
}

int hashmap_has_key(hashmap_t _map, any_t key)
{
    HASHMAP_INSTANCE(_map);
    return map->impl->_hashmap_has_key(map->instance, key);
}

uint hsahmap_size(hashmap_t _map)
{
    HASHMAP_INSTANCE(_map);
    return map->impl->_hashmap_size(map->instance);
}

void hashmap_iterate(hashmap_t _map, PFany fptr, any_t args)
{
    HASHMAP_INSTANCE(_map);
    return map->impl->_hashmap_iterate(map->instance, fptr, args);
}

void hashmap_insert(hashmap_t _map, any_t key, any_t value)
{
    HASHMAP_INSTANCE(_map);
    return map->impl->_hashmap_insert(map->instance, key, value);
}

void hashmap_remove(hashmap_t _map, any_t key)
{
    HASHMAP_INSTANCE(_map);
    return map->impl->_hashmap_remove(map->instance, key);
}

void hashmap_dump(hashmap_t _map, printFunc print_fn)
{
    HASHMAP_INSTANCE(_map);
    map->impl->_hashmap_dump(map->instance, print_fn);
}

void hashmap_probing(hashmap_t _map, int type)
{
    HASHMAP_INSTANCE(_map);
    map->impl->_hashmap_probing(map->instance, type);
}