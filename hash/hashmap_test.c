#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

static void print_int(void *val)
{
    if (val)
        printf(" %d", *(int *)val);
}

int main(int argc, char **argv)
{
    hashmap_t map = hashmap_create(HASHMAP_CHAINING, hash_int, hash_int_equal);

    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    for (int i = 0; i < 16; i++)
        hashmap_insert(map, &arr[i], &arr[i]);
    
    hashmap_dump(map, print_int);

    return 0;
}
