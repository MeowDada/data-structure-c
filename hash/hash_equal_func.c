#include "hashmap.h"

HashEqualFunc hash_int_equal(const int *lhs, const int *rhs)
{
    return *lhs == *rhs ? 1 : 0;
}

