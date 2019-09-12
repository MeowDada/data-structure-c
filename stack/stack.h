#ifndef STACK_H
#define STACK_H
#include "common.h"

typedef any_t stack_t;

enum {
    STACK_IMPL_BY_ARRAY,
    STACK_IMPL_BY_VECTOR,
    STACK_IMPL_BY_LINKED_LIST
};

extern stack_t stack_create(int);
extern void    stack_destroy(stack_t);
extern void    stack_clear(stack_t);
extern void    stack_push(stack_t, any_t);
extern any_t   stack_pop(stack_t);
extern void    stack_dump(stack_t, printFunc);
extern any_t   stack_top(stack_t);
extern int     stack_is_empty(stack_t);
extern int     stack_size(stack_t);

#endif /* STACK_H */