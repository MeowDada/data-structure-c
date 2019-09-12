#include "stack_impl.h"

stack_impl stack_impl_table[] = {
    [STACK_IMPL_BY_ARRAY] = &stack_impl_by_array,
    [STACK_IMPL_BY_VECTOR] = &stack_impl_by_vector,
    [STACK_IMPL_BY_LINKED_LIST] = &stack_impl_by_linked_list
}