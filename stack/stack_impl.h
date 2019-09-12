#ifndef STACK_IMPL_H
#define STACK_IMPL_H
#include "stack.h"

typedef struct _stack_impl *stack_impl;
struct _stack_impl {
    stack_t (*_stack_create)();
    void    (*_stack_destroy)(stack_t);
    void    (*_stack_clear)(stack_t);
    void    (*_stack_push)(stack_t, any_t);
    any_t   (*_stack_pop)(stack_t);
    void    (*_stack_dump)(stack_t, printFunc);
    any_t   (*_stack_top)(stack_t);
    int     (*_stack_is_empty)(stack_t);
    int     (*_stack_size)(stack_t);
};

extern stack_impl stack_impl_table[];
extern stack_impl stack_impl_by_array;
extern stack_impl stack_impl_by_vector;
extern stack_impl stack_impl_by_linked_list;

#endif /* STACK_IMPL_H */