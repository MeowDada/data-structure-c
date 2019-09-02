#include <stdio.h>
#include "vector.h"

static void basic_test_case(void *vector)
{
    int arr1[] = {6,7,8,9,10};
    int arr2[] = {5,4,3,2,1};
    
    for (int i = 0; i < 5; i++)
        vector_push_back(vector, &arr1[i]);
    for (int i = 0; i < 5; i++)
        vector_push_front(vector, &arr2[i]);
    vector_info(vector);
    vector_dump(vector, vector_print_int);

    void *elem = vector_pop_back(vector);
    vector_dump(vector, vector_print_int);
    printf("pop item = %d\n", *(int *)elem);

    elem = vector_pop_front(vector);
    vector_dump(vector, vector_print_int);
    printf("pop item = %d\n", *(int *)elem);

    elem = vector_pop_front(vector);
    vector_dump(vector, vector_print_int);
    printf("pop item = %d\n", *(int *)elem);

    elem = vector_pop_front(vector);
    vector_dump(vector, vector_print_int);
    printf("pop item = %d\n", *(int *)elem);

    elem = vector_pop_front(vector);
    vector_dump(vector, vector_print_int);
    printf("pop item = %d\n", *(int *)elem);

    elem = vector_pop_front(vector);
    vector_dump(vector, vector_print_int);
    if (elem)
        printf("pop item = %d\n", *(int *)elem);
    else
        printf("pop item = (nil)\n");
}

int main(int argc, char **argv)
{
    vector_t vector = vector_create(sizeof(int));
    if (!vector) {
        fprintf(stderr, "could not allocate memory for vector\n");
        return -1;
    }

    basic_test_case(vector);

    return 0;
}