#ifndef QUEUE_H
#define QUEUE_H
#include "common.h"

typedef any_t queue_t;

enum {
    QUEUE_IMPL_BY_ARRAY       = 0,
    QUEUE_IMPL_BY_VECTOR      = 1,
    QUEUE_IMPL_BY_LINKED_LIST = 2
};

extern queue_t queue_create(int, any_t, any_t);
extern int     queue_is_empty(queue_t);
extern int     queue_is_full(queue_t);
extern int     queue_size(queue_t);
extern void    queue_enqueue(queue_t, any_t);
extern any_t   queue_dequeue(queue_t);
extern void    queue_destroy(queue_t _q)

#endif /* QUEUE_H */