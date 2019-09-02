#include <stdio.h>
#include "vector.h"

int main(int argc, char **argv)
{
    vector_t vector = vector_create();
    if (!vector) {
        fprintf(stderr, "could not allocate memory for vector\n");
        return -1;
    }

    int arr[] = {1,2,3,4,5};
    for (int i = 0; i < 5; i++)
        vector_push_back(vector, &arr[i]);
    vector_dump(vector, vector_print_int);

    return 0;
}