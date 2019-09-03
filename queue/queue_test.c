#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, char **argv)
{
    int capacity = 10;
    size_t sizeof_int = sizeof(int);
    queue_t q = queue_create(QUEUE_IMPL_BY_ARRAY, &capacity, &sizeof_int);

    int arr[] = {0,1,2,3,4,5,6,7,8,9};
    for (int i = 0; i < 5; i++) {
        queue_enqueue(q, &arr[i]);
    }

    for (int i = 0; i < 10; i++) {
        void *item = queue_dequeue(q);
        printf("%d ", *(int *)item);
    }
    printf("\n");

    return 0;
}