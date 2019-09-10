#ifndef HASHMAP_IMPL_H
#define HASHMAP_IMPL_H
#include "hashmap.h"

typedef struct hashmap_impl {
    void     *(*_hashmap_create)(HashFunc hash_func, HashEqualFunc equal_func);
    void      (*_hashmap_destroy)(hashmap_t map);
    any_t     (*_hashmap_find)(hashmap_t map, any_t key);
    int       (*_hashmap_has_key)(hashmap_t map, any_t key);
    uint      (*_hashmap_size)(hashmap_t map);
    void      (*_hashmap_iterate)(hashmap_t map, PFany fptr, any_t args);
    void      (*_hashmap_insert)(hashmap_t map, any_t key, any_t value);
    void      (*_hashmap_remove)(hashmap_t map, any_t key);
    void      (*_hashmap_dump)(hashmap_t map, printFunc);
    void      (*_hashmap_probing)(hashmap_t map, int type);
} hashmap_impl;

extern hashmap_impl hashmap_impl_table[2];

/* hashmap implemented by chaining */
extern void     *hashmap_chaining_create(HashFunc, HashEqualFunc);
extern void      hashmap_chaining_destroy(hashmap_t);
extern any_t     hashmap_chaining_find(hashmap_t, any_t);
extern int       hashmap_chaining_has_key(hashmap_t, any_t);
extern uint      hashmap_chaining_size(hashmap_t);
extern void      hashmap_chaining_iterate(hashmap_t, PFany, any_t);
extern void      hashmap_chaining_insert(hashmap_t, any_t, any_t);
extern void      hashmap_chaining_remove(hashmap_t, any_t);
extern void      hashmap_chaining_dump(hashmap_t, printFunc);
extern void      hashmap_chaining_probing(hashmap_t, int);

/* hashmap implemented by open addressing */
extern void     *hashmap_open_addressing_create(HashFunc, HashEqualFunc);
extern void      hashmap_open_addressing_destroy(hashmap_t);
extern any_t     hashmap_open_addressing_find(hashmap_t, any_t);
extern int       hashmap_open_addressing_has_key(hashmap_t, any_t);
extern uint      hashmap_open_addressing_size(hashmap_t);
extern void      hashmap_open_addressing_iterate(hashmap_t, PFany, any_t);
extern void      hashmap_open_addressing_insert(hashmap_t, any_t, any_t);
extern void      hashmap_open_addressing_remove(hashmap_t, any_t);
extern void      hashmap_open_addressing_dump(hashmap_t, printFunc);
extern void      hashmap_open_addressing_probing(hashmap_t, int);

#endif /* HASHMAP_IMPL_H */