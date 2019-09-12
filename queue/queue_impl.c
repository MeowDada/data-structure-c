#include "queue.h"
#include "queue_impl.h"

queue_impl queue_impl_table[] = {
    [QUEUE_IMPL_BY_ARRAY] = {
        ._queue_create   = queue_create_impl_by_array,
        ._queue_is_empty = queue_is_empty_impl_by_array,
        ._queue_is_full  = queue_is_full_impl_by_array,
        ._queue_size     = queue_size_impl_by_array,
        ._queue_enqueue  = queue_enqueue_impl_by_array,
        ._queue_dequeue  = queue_dequeue_impl_by_array,
        ._queue_clear    = queue_clear_impl_by_array,
        ._queue_destroy  = queue_destroy_impl_by_array
    },
    [QUEUE_IMPL_BY_LINKED_LIST] = {
        ._queue_create   = queue_create_impl_by_vector,
        ._queue_is_empty = queue_is_empty_impl_by_vector,
        ._queue_is_full  = queue_is_full_impl_by_vector,
        ._queue_size     = queue_size_impl_by_vector,
        ._queue_enqueue  = queue_enqueue_impl_by_vector,
        ._queue_dequeue  = queue_dequeue_impl_by_vector,
        ._queue_clear    = queue_clear_impl_by_vector,
        ._queue_destroy  = queue_destroy_impl_by_vector
    },
    [QUEUE_IMPL_BY_VECTOR] = {
        ._queue_create   = queue_create_impl_by_linked_list,
        ._queue_is_empty = queue_is_empty_impl_by_linked_list,
        ._queue_is_full  = queue_is_full_impl_by_linked_list,
        ._queue_size     = queue_size_impl_by_linked_list,
        ._queue_enqueue  = queue_enqueue_impl_by_linked_list,
        ._queue_dequeue  = queue_dequeue_impl_by_linked_list,
        ._queue_clear    = queue_clear_impl_by_linked_list,
        ._queue_destroy  = queue_destroy_impl_by_linked_list
    },
};