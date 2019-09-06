#include "hashmap.h"

int hash_int_equal(const void *lhs, const void *rhs)
{
    int l = *(int *)lhs;
    int r = *(int *)rhs;
    return l == r ? 1 : 0;
}

