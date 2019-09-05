#ifndef HASHMAP_IMPL_H
#define HASHMAP_IMPL_H
#include "hashmap.h"

typedef struct hashmap_impl {
    void     *(*_hashmap_create)(HashFunc hash_func, HashEqualFunc equal_func);
    void      (*_hashmap_destroy)(hashmap_t map);
    any_t     (*_hashmap_find)(hashmap_t map, any_t key);
    int       (*_hashmap_has_key)(hashmap_t map, any_t key);
    int       (*_hashmap_size)(hashmap_t map);
    void      (*_hashmap_iterate)(hashmap_t map, PFany fptr, any_t args);
    void      (*_hashmap_insert)(hashmap_t map, any_t key, any_t value);
    void      (*_hashmap_remove)(hashmap_t map, any_t key);
} hashmap_impl;

extern const hashmap_impl hashmap_impl_table[2];

extern void     *hashmap_chaining_create(HashFunc, HashEqualFunc);
extern void      hashmap_chaining_destroy(hashmap_t);
extern any_t     hashmap_chaining_find(hashmap_t, any_t);
extern int       hashmap_chaining_has_key(hashmap_t, any_t);
extern int       hashmap_chaining_size(hashmap_t);
extern void      hashmap_chaining_iterate(hashmap_t, PFany, any_t);
extern void      hashmap_chaining_insert(hashmap_t, any_t, any_t);
extern void      hashmap_chaining_remove(hashmap_t, any_t);

#endif /* HASHMAP_IMPL_H */