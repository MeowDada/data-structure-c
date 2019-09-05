#include <stdlib.h>
#include "hashmap_impl.h"

hashmap_impl hashmap_impl_table[] = {
    [HASHMAP_CHAINING] = {
        ._hashmap_create  = hashmap_chaining_create,
        ._hashmap_destroy = hashmap_chaining_destroy,
        ._hashmap_find    = hashmap_chaining_find,
        ._hashmap_has_key = hashmap_chaining_has_key,
        ._hashmap_size    = hashmap_chaining_size,
        ._hashmap_iterate = hashmap_chaining_iterate,
        ._hashmap_insert  = hashmap_chaining_insert,
        ._hashmap_remove  = hashmap_chaining_remove,
    },
    [HASHMAP_DOUBLE_HASHING] = {

    },
};