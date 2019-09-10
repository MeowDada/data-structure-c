#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

static void print_int(void *val)
{
    if (val)
        printf(" %d", *(int *)val);
    else
        printf(" (nil)");
}

int main(int argc, char **argv)
{
    hashmap_t map = hashmap_create(HASHMAP_OPEN_ADDRESSING, hash_int, hash_int_equal);
    hashmap_probing(map, HASHMAP_DOUBLE_HASHING);

    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

    int arr2[] = {50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 100, 101, 102, 103, 104};

    for (int i = 0; i < 32; i++)
        hashmap_insert(map, &arr[i], &arr[i]);
    hashmap_dump(map, print_int);

    int key = 5;
    void *val = hashmap_find(map, &key);
    print_int(val);
    printf("\n");

    key = 10;
    val = hashmap_find(map, &key);
    print_int(val);
    printf("\n");

    key = 50;
    val = hashmap_find(map, &key);
    print_int(val);
    printf("\n");

    for (int i = 0; i < 10; i++) {
        key = i;
        hashmap_remove(map, &key);
    }
    for (int i = 0; i < 15; i++) 
        hashmap_insert(map, &arr2[i], &arr2[i]);
    
    hashmap_dump(map, print_int);

    hashmap_destroy(map);

    return 0;
}

