#include <stdio.h>
#include <stdlib.h>
#include "single_linked_list.h"

static int print_int(void *node, void *args)
{
    if (node)
        printf("%d ", *(int *)node);
    else
        printf("(nil)");
    return 0;
}

static void print(void *node)
{
    if (node)
        printf("%d\n", *(int *)node);
    else
        printf("(nil)\n");
}

int main(int argc, char **argv)
{
    int arr[] = {1,2,3,4,5};
    s_llst_t node[5];
    for (int i = 0; i < 5; i++) {
        node[i] = single_linked_list_create(&arr[i], sizeof(int));
        single_linked_list_dump_node(node[i], print);
    }

    single_linked_list_append(node[0], node[1]);
    single_linked_list_append(node[0], node[2]);
    single_linked_list_append(node[0], node[3]);
    single_linked_list_append(node[0], node[4]);
    single_linked_list_iterate(node[0], print_int, NULL);

    return 0;
}