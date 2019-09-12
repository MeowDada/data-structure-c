#ifndef QUEUE_IMPL_H
#define QUEUE_IMPL_H

typedef struct queue_impl {
    void *(*_queue_create)(void *, void *);
    int   (*_queue_is_empty)(void *);
    int   (*_queue_is_full)(void *);
    int   (*_queue_size)(void *);
    void  (*_queue_enqueue)(void *, void *);
    void *(*_queue_dequeue)(void *);
    void  (*_queue_clear)(void *);
    void  (*_queue_destroy)(void *);
} queue_impl;

extern queue_impl queue_impl_table[];

void *queue_create_impl_by_array(void *, void *);
int   queue_is_empty_impl_by_array(void *);
int   queue_is_full_impl_by_array(void *);
int   queue_size_impl_by_array(void *);
void  queue_enqueue_impl_by_array(void *, void *);
void *queue_dequeue_impl_by_array(void *);
void  queue_clear_impl_by_array(void *);
void  queue_destroy_impl_by_array(void *);

void *queue_create_impl_by_vector(void *, void *);
int   queue_is_empty_impl_by_vector(void *);
int   queue_is_full_impl_by_vector(void *);
int   queue_size_impl_by_vector(void *);
void  queue_enqueue_impl_by_vector(void *, void *);
void *queue_dequeue_impl_by_vector(void *);
void  queue_clear_impl_by_vector(void *);
void  queue_destroy_impl_by_vector(void *);

void *queue_create_impl_by_linked_list(void *, void *);
int   queue_is_empty_impl_by_linked_list(void *);
int   queue_is_full_impl_by_linked_list(void *);
int   queue_size_impl_by_linked_list(void *);
void  queue_enqueue_impl_by_linked_list(void *, void *);
void *queue_dequeue_impl_by_linked_list(void *);
void  queue_clear_impl_by_linked_list(void *);
void  queue_destroy_impl_by_linked_list(void *);

#endif /* QUEUE_IMPL_H */