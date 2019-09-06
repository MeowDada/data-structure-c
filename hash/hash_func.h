#ifndef HASH_FUNC_H
#define HASH_FUNC_H
#include "common.h"

extern uint  hash_int(const any_t);
extern uint  hash_direct(const any_t);
extern const uint prime_mode[];

#endif /* HASH_FUNC_H */