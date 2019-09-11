#ifndef HASH_EQUAL_FUNC_H
#define HASH_EQUAL_FUNC_H
#include "common.h"

extern int hash_uint_equal(const any_t , const any_t);
extern int hash_uint8_equal(const any_t, const any_t);
extern int hash_uint16_equal(const any_t, const any_t);
extern int hash_uint32_equal(const any_t, const any_t);
extern int hash_uint64_equal(const any_t, const any_t);

extern int hash_int_equal(const any_t, const any_t);
extern int hash_int8_equal(const any_t, const any_t);
extern int hash_int16_equal(const any_t, const any_t);
extern int hash_int32_equal(const any_t, const any_t);
extern int hash_int64_equal(const any_t, const any_t);

extern int hash_string_equal(const any_t, const any_t);

#endif /* HASH_EQUAL_FUNC_H */