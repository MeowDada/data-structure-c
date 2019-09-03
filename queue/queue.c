#include <stdlib.h>
#include "queue.h"
#include "queue_impl.h"

#define QUEUE_INSTANCE queue *q = (queue *)_q;

typedef struct queue {
    queue_impl *impl;
    any_t       instance;
} queue;

queue_t queue_create(int impl, any_t arg1, any_t arg2)
{
    queue *q    = calloc(1, sizeof(queue));
    if (!q)
        return NULL;
    
    q->impl     = queue_impl_table[impl];
    q->instance = q->impl->_queue_create(arg1, arg2);

    return q;
}

int queue_is_empty(queue_t _q)
{
    QUEUE_INSTANCE
    return q->impl->_queue_is_empty(q->instance);
}

int queue_is_full(queue_t _q)
{
    QUEUE_INSTANCE
    return q->impl->_queue_is_full(q->instance);
}

int queue_size(queue_t _q)
{
    QUEUE_INSTANCE
    return q->impl->_queue_size(q->instance);
}

void queue_enqueue(queue_t _q, any_t data)
{
    QUEUE_INSTANCE
    q->impl->_queue_enqueue(q->instance, data);
}

any_t queue_dequeue(queue_t _q)
{
    QUEUE_INSTANCE
    return q->impl->_queue_dequeue(q->instance);
}

void queue_destroy(queue_t _q)
{
    if (!_q)
        return;
    
    QUEUE_INSTANCE
    q->impl->_queue_destroy(q->instance);
    q->impl = NULL;
    free(q);
}