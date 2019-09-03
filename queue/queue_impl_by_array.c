#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "queue.h"
#define QUEUE_INSTANCE queue *q = (queue *)_q;

typedef struct queue {
    int     capacity;
    int     front;
    int     rear;
    int     size;
    size_t  sizeof_data;
    void   *data;
} queue;

static void *queue_at(queue *q, int idx)
{
    char *data = (char *)q->data;
    return data + idx*q->sizeof_data;
}

void *queue_create_impl_by_array(void *capacity, void *size)
{
    queue *q    = calloc(1, sizeof(queue));
    if (!q)
        return NULL;

    q->capacity    = *(int *)capacity;
    q->size        = 0;
    q->front       = 0;
    q->rear        = 0;
    q->sizeof_data = *(size_t *)size;
    q->data        = calloc(q->capacity, *(size_t *)size);
    if (!q->data) {
        free(q);
        return NULL;
    }
    return q;
}

int queue_is_empty_impl_by_array(void *_q)
{
    QUEUE_INSTANCE
    if (q->size == 0 && q->rear == q->front)
        return 1;
    return 0;
}

int queue_is_full_impl_by_array(void *_q)
{
    QUEUE_INSTANCE
    if (q->size == q->capacity && q->rear == q->front)
        return 1;
    return 0;
}

int queue_size_impl_by_array(void *_q)
{
    QUEUE_INSTANCE
    return q->size;
}

void  queue_enqueue_impl_by_array(void *_q, void *data)
{
    QUEUE_INSTANCE
    if (q->capacity > q->size && q->front != q->rear) {
        memcpy(queue_at(q, q->rear), data, q->sizeof_data);
        q->rear = (q->rear + 1) % q->capacity;
        q->size++;
    }
}

void *queue_dequeue_impl_by_array(void *_q)
{
    QUEUE_INSTANCE
    if (q->size > 0) {
        void *data = queue_at(q, q->front);
        q->front = (q->front + 1) % q->capacity;
        q->size--;
        return data;
    }

    return NULL;
}

void queue_destroy_impl_by_array(void *_q)
{
    if (!_q)
        return;

    QUEUE_INSTANCE
    free(q->data);
    free(q);
}