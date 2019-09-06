#include "hashmap.h"

int hash_int_equal(const any_t lhs, const any_t rhs)
{
    int l = *(int *)lhs;
    int r = *(int *)rhs;
    return l == r ? 1 : 0;
}

