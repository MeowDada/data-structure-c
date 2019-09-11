#ifndef HASHMAP_H
#define HASHMAP_H
#include "common.h"
#include "hash_func.h"
#include "hash_equal_func.h"

typedef any_t  hashmap_t;
typedef any_t  hashmap_iter_t;
typedef uint  (*HashFunc) (const any_t);
typedef int   (*HashEqualFunc) (const any_t, const any_t);

enum {
    HASHMAP_CHAINING       = 0,
    HASHMAP_OPEN_ADDRESSING = 1,
};

enum {
    HASHMAP_MISS = 0,
    HASHMAP_HIT  = 1,
};

enum {
    HASHMAP_LINEAR_PROBING    = 0,
    HASHMAP_QUADRATIC_PROBING = 1,
    HASHMAP_DOUBLE_HASHING    = 2,
};

extern hashmap_t hashmap_create(int type, HashFunc hash_func, HashEqualFunc equal_func);
extern void      hashmap_destroy(hashmap_t map);
extern any_t     hashmap_find(hashmap_t map, any_t k);
extern int       hashmap_has_key(hashmap_t map, any_t k);
extern uint      hsahmap_size(hashmap_t map);
extern void      hashmap_iterate(hashmap_t map, PFany fptr, any_t args);
extern void      hashmap_insert(hashmap_t map, any_t k, any_t v);
extern void      hashmap_remove(hashmap_t map, any_t k);
extern void      hashmap_dump(hashmap_t map, printFunc);
extern void      hashmap_probing(hashmap_t map, int type);

#endif /* HASHMAP_H */