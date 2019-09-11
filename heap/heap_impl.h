#ifndef HEAP_IMPL_H
#define HEAP_IMPL_H
#include "common.h"

typedef struct heap_impl {
    void   *(*_heap_create)();
    void    (*_heap_destroy)();
    void    (*_heap_insert)();
    void    (*_heap_extract)();
    any_t   (*_heap_find_min)();
}heap_impl;

#endif /* HEAP_IMPL_H */