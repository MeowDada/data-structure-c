#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static void queue_basic_test(queue_t q)
{
    int arr[] = {0,1,2,3,4,5,6,7,8,9};
    for (int i = 0; i < 8; i++) {
        queue_enqueue(q, &arr[i]);
    }

    for (int i = 0; i < 10; i++) {
        void *item = queue_dequeue(q);
        if (item)
            printf("%d ", *(int *)item);
        else
            printf("(nil) ");
    }
    printf("\n");

    queue_destroy(q);
}

int main(int argc, char **argv)
{
    int capacity = 5;
    size_t sizeof_int = sizeof(int);
    queue_t q_arr = queue_create(QUEUE_IMPL_BY_ARRAY, &capacity, &sizeof_int);
    queue_t q_vec = queue_create(QUEUE_IMPL_BY_VECTOR, &sizeof_int, NULL);
    queue_t q_ll  = queue_create(QUEUE_IMPL_BY_LINKED_LIST, &sizeof_int, NULL);
    queue_basic_test(q_arr);
    queue_basic_test(q_vec);
    queue_basic_test(q_ll);

    return 0;
}