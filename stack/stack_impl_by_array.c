#include <stdlib.h>
#include <memory.h>
#include "stack_impl.h"

#define DEFAULT_CAPACITY (1 << 5)
#define STACK_INSTANCE(_ptr,instance) stack *instance = (stack *)(_ptr)

typedef struct stack {
    int    size;
    int    capacity;
    any_t *data
} stack;

static inline int stack_is_full(stack *s)
{
    return s->capacity == s->data ? 1 : 0;
}

static void stack_resize_larger(stack *s)
{
    s->capacity <<= 1;
    void *temp = realloc(s->data, s->capacity);
    if (temp)
        s->data = temp;
}

stack *stack_impl_array_create()
{
    stack *s = calloc(1, sizeof(stack));
    if (!s)
        return NULL;
    
    s->size     = 0;
    s->capacity = DEFAULT_CAPACITY;
    s->data     = calloc(1, s->capacity * sizeof(any_t));

    return s;
}

void stack_impl_array_destroy(stack_t _s)
{
    STACK_INSTANCE(_s, s);
    if (s->data) {
        free(s->data);
        s->data = NULL;
    }
    free(s);
}

void stack_impl_array_clear(stack_t _s)
{
    STACK_INSTANCE(_s, s);
    for (int i = 0 ; i < s->capacity; i++)
        s->data[i] = NULL;
    s->size = 0;
}

void stack_impl_array_push(stack_t _s, any_t data)
{
    STACK_INSTANCE(_s, s);
    if (stack_is_full(s))
        stack_resize_larger(s);

    s->data[s->size] = data;
    s->size++;
}

any_t stack_impl_array_pop(stack_t _s)
{
    STACK_INSTANCE(_s, s);
    if (s->size > 0) {
        void *ret = s->data[s->size-1];
        s->size--;
        return ret;
    }
    return NULL;
}

void stack_impl_array_dump(stack_t _s, printFunc fptr)
{
    STACK_INSTANCE(_s, s);
    printf("[");
    for (int i = 0; i < s->capacity; i++)
        (*fptr)(s->data[i]);
    printf(" ]\n");
}

any_t stack_impl_array_top(stack_t _s)
{
    STACK_INSTANCE(_s, s);
    if (s->size > 0) {
        return s->data[s->size-1];
    }
    return NULL;
}
int stack_impl_array_is_empty(stack_t _s)
{
    STACK_INSTANCE(_s, s);
    return s->size == 0 ? 1 : 0;
}

int stack_impl_array_size(stack_t _s)
{
    STACK_INSTANCE(_s, s);
    return s->size;
}

struct _stack_impl stack_impl_by_array = {
    ._stack_create   = stack_impl_array_create,
    ._stack_destroy  = stack_impl_array_destroy,
    ._stack_clear    = stack_impl_array_clear,
    ._stack_push     = stack_impl_array_push,
    ._stack_pop      = stack_impl_array_pop,
    ._stack_dump     = stack_impl_array_dump,
    ._stack_top      = stack_impl_array_top,
    ._stack_is_empty = stack_impl_array_is_empty,
    ._stack_size     = stack_impl_array_size,
};