#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "queue.h"
#include "linked_list.h"

#define QUEUE_INSTANCE queue *q = (queue *)_q;

typedef struct queue {
    linked_list_t *list;
    int size;
    size_t sizeof_elem;
} queue;

void *queue_create_impl_by_linked_list(void *size, void *dump)
{
    queue *q = calloc(1, sizeof(queue));
    if (!q)
        return NULL;
    
    q->size = 0;
    q->list = NULL;
    q->sizeof_elem = *(size_t *)size;

    return q;
}

int queue_is_empty_impl_by_linked_list(void *_q)
{
    QUEUE_INSTANCE
    return q->size == 0 ? 1 : 0;
}

int queue_is_full_impl_by_linked_list(void *_q)
{
    return 0;
}

int queue_size_impl_by_linked_list(void *_q)
{
    QUEUE_INSTANCE
    return q->size;
}

void queue_enqueue_impl_by_linked_list(void *_q, void *data)
{
    QUEUE_INSTANCE
    if (!q->list && q->size == 0) {
        q->list = linked_list_create(data, q->sizeof_elem);
    }

    if (q->list) {
        linked_list_t *node = linked_list_create(data, q->sizeof_elem);
        q->list = linked_list_insert_tail(q->list, node);
    }
}

void *queue_dequeue_impl_by_linked_list(void *_q)
{
    QUEUE_INSTANCE
    if (q->list && q->size > 0) {
        void *val = linked_list_get_value(q->list);
        void *copy = calloc(1, q->sizeof_elem);
        memcpy(copy, val, q->sizeof_elem);
        q->list = linked_list_delete_head(q->list);
        return copy;
    }
    return NULL;
}

void  queue_destroy_impl_by_linked_list(void *_q)
{
    if (!_q)
        return;
    QUEUE_INSTANCE
    linked_list_destroy_list(q->list);
    q->list = NULL;
    free(q);
}