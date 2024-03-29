#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "queue.h"
#include "vector.h"

#define QUEUE_INSTANCE queue *q = (queue *)_q;

void *queue_create_impl_by_vector(void *_size, void *dump)
{
    size_t size = *(size_t *)_size;
    vector_t v = vector_create(size);
    return v;
}

int queue_is_empty_impl_by_vector(void *_q)
{
    return vector_size(_q) == 0? 1 : 0;
}

int queue_is_full_impl_by_vector(void *_q)
{
    return vector_size(_q) == vector_capacity(_q)? 1 : 0;
}

int queue_size_impl_by_vector(void *_q)
{
    return vector_size(_q);
}

void queue_enqueue_impl_by_vector(void *_q, void *data)
{
    vector_push_back(_q, data);
}

void *queue_dequeue_impl_by_vector(void *_q)
{
    return vector_pop_front(_q);
}

void queue_clear_impl_by_vector(void *_q)
{
    return vector_clear(_q);
}

void queue_destroy_impl_by_vector(void *_q)
{
    vector_destroy(&_q);
}