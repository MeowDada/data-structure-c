#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "hashmap.h"

int hash_uint_equal(const any_t lhs, const any_t rhs)
{
    uint l = *(uint *)lhs;
    uint r = *(uint *)rhs;
    return l == r ? 1 : 0;
}

int hash_uint8_equal(const any_t lhs, const any_t rhs)
{
    uint8_t l = *(uint8_t *)lhs;
    uint8_t r = *(uint8_t *)rhs;
    return l == r ? 1 : 0;
}

int hash_uint16_equal(const any_t lhs, const any_t rhs)
{
    uint16_t l = *(uint16_t *)lhs;
    uint16_t r = *(uint16_t *)rhs;
    return l == r ? 1 : 0;
}

int hash_uint32_euqal(const any_t lhs, const any_t rhs)
{
    return hash_uint_equal(lhs, rhs);
}

int hash_uint64_equal(const any_t lhs, const any_t rhs)
{
    uint64_t l = *(uint64_t *)lhs;
    uint64_t r = *(uint64_t *)rhs;
    return l == r ? 1 : 0;
}

int hash_int_equal(const any_t lhs, const any_t rhs)
{
    int l = *(int *)lhs;
    int r = *(int *)rhs;
    return l == r ? 1 : 0;
}

int hash_int8_equal(const any_t lhs, const any_t rhs)
{
    int8_t l = *(int8_t *)lhs;
    int8_t r = *(int8_t *)rhs;
    return l == r ? 1 : 0;
}

int hash_int16_equal(const any_t lhs, const any_t rhs)
{
    int16_t l = *(int16_t *)lhs;
    int16_t r = *(int16_t *)rhs;
    return l == r ? 1 : 0;
}

int hash_int32_equal(const any_t lhs, const any_t rhs)
{
    return hash_int_equal(lhs, rhs);
}

int hash_int64_equal(const any_t lhs, const any_t rhs)
{
    int64_t l = *(int64_t *)lhs;
    int64_t r = *(int64_t *)rhs;
    return l == r ? 1 : 0;
}

int hash_string_equal(const any_t lhs, const any_t rhs)
{
    return strcmp(lhs, rhs) == 0 ? 1 : 0;
}

