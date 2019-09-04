#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static void queue_basic_test(int type)
{
    int capacity = 5;
    size_t sizeof_int = sizeof(int);
    queue_t q = queue_create(type, &capacity, &sizeof_int);

    int arr[] = {0,1,2,3,4,5,6,7,8,9};
    for (int i = 0; i < 7; i++) {
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
    queue_basic_test(QUEUE_IMPL_BY_ARRAY);
    queue_basic_test(QUEUE_IMPL_BY_VECTOR);
    queue_basic_test(QUEUE_IMPL_BY_LINKED_LIST);

    return 0;
}