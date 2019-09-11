#include "queue_impl.h"

struct _queue_impl {
    void *(*_queue_create)(void *, void *);
    int   (*_queue_is_empty)(void *);
    int   (*_queue_is_full)(void *);
    int   (*_queue_size)(void *);
    void  (*_queue_enqueue)(void *, void *);
    void *(*_queue_dequeue)(void *);
    void  (*_queue_destroy)(void *);
};

queue_impl queue_impl_by_array = {
    ._queue_create   = queue_create_impl_by_array,
    ._queue_is_empty = queue_is_empty_impl_by_array,
    ._queue_is_full  = queue_is_full_impl_by_array,
    ._queue_size     = queue_size_impl_by_array,
    ._queue_enqueue  = queue_enqueue_impl_by_array,
    ._queue_dequeue  = queue_dequeue_impl_by_array,
    ._queue_destroy  = queue_destroy_impl_by_array
};

queue_impl queue_impl_by_vector = {
    ._queue_create   = queue_create_impl_by_vector,
    ._queue_is_empty = queue_is_empty_impl_by_vector,
    ._queue_is_full  = queue_is_full_impl_by_vector,
    ._queue_size     = queue_size_impl_by_vector,
    ._queue_enqueue  = queue_enqueue_impl_by_vector,
    ._queue_dequeue  = queue_dequeue_impl_by_vector,
    ._queue_destroy  = queue_destroy_impl_by_vector
};

queue_impl queue_impl_by_linked_list = {
    ._queue_create   = queue_create_impl_by_linked_list,
    ._queue_is_empty = queue_is_empty_impl_by_linked_list,
    ._queue_is_full  = queue_is_full_impl_by_linked_list,
    ._queue_size     = queue_size_impl_by_linked_list,
    ._queue_enqueue  = queue_enqueue_impl_by_linked_list,
    ._queue_dequeue  = queue_dequeue_impl_by_linked_list,
    ._queue_destroy  = queue_destroy_impl_by_linked_list
};