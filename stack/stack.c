#include <stdlib.h>
#include <memory.h>
#include "stack.h"
#include "stack_impl.h"

#define STACK_INSTANCE(_ptr,instance) struct _stack_t *instance = (struct _stack_t *)(_ptr)

typedef struct _stack_t {
    any_t      instance;
    stack_impl impl;
} _stack_t;

stack_t stack_create(int type) {
    struct _stack_t *stack = calloc(1, sizeof(struct _stack_t));
    if (!stack)
        return NULL;

    stack->impl = stack_impl_table[type];
    stack->instance = stack->impl->_stack_create();
    if (!stack->instance) {
        free(stack);
        return NULL;
    }
    return stack;
}

void stack_destroy(stack_t _stack)
{
    if (!_stack)
        return;
    
    STACK_INSTANCE(_stack, stack);
    stack->impl->_stack_destroy(stack->instance);
    free(_stack);
}

void stack_clear(stack_t _stack)
{
    if (!_stack)
        return;
    
    STACK_INSTANCE(_stack, stack);
    stack->impl->_stack_clear(stack->instance);
}

void stack_push(stack_t _stack, any_t data)
{
    if (!_stack)
        return;
    
    STACK_INSTANCE(_stack, stack);
    stack->impl->_stack_push(stack->instance, data);
}

any_t stack_pop(stack_t _stack)
{
    if (!_stack)
        return;
    
    STACK_INSTANCE(_stack, stack);
    return stack->impl->_stack_pop(stack->instance);
}

void stack_dump(stack_t _stack, printFunc fptr)
{
    if (!_stack || !fptr)
        return;
    
    STACK_INSTANCE(_stack, stack);
    stack->impl->_stack_dump(stack->instance, fptr);
}

any_t stack_top(stack_t _stack)
{
    if (!_stack)
        return NULL;
    
    STACK_INSTANCE(_stack, stack);
    stack->impl->_stack_top(stack->instance);
}

int stack_is_empty(stack_t _stack)
{
    if (!_stack)
        return 1;
    
    STACK_INSTANCE(_stack, stack);
    stack->impl->_stack_is_empty(stack->instance);
}

int stack_size(stack_t _stack)
{
    if (!_stack)
        return 0;
    
    STACK_INSTANCE(_stack, stack);
    stack->impl->_stack_size(stack->instance);
}