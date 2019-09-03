#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "linked_list.h"

typedef struct list_t list_t;

struct list_t {
    list_t *next;
    list_t *prev;
    any_t   data;
    size_t  size;
};

linked_list_t linked_list_create(any_t data, size_t size)
{
    if (!data || size == 0)
        return NULL;
    
    list_t *node = calloc(1, sizeof(list_t));
    if (!node)
        return NULL;
    
    node->data = calloc(1, size);
    if (!node->data) {
        free(node);
        return NULL;
    }

    node->prev = NULL;
    node->next = NULL;
    node->size = size;
    memcpy(node->data, data, size);

    return node;
}

void linked_list_append(linked_list_t _node, linked_list_t _new_node)
{
    if (!_node || !_new_node)
        return;
    
    list_t *node = (list_t *)_node;
    list_t *new_node = (list_t *)_new_node;
    list_t *next_node = node->next;
    node->next = new_node;
    if (next_node)
        next_node->prev = new_node;
    new_node->next = next_node;
    new_node->prev = node;
}

void linked_list_delete(linked_list_t _node)
{
    if (!_node)
        return;
    
    list_t *node = (list_t *)_node;
    list_t *prev = node->prev;
    list_t *next = node->next;
    linked_list_destroy(_node);
    node = NULL;
    if (prev)
        prev->next = next;
    if (next)
        next->prev = prev;
}

any_t linked_list_get_value(linked_list_t _node)
{
    list_t *node = (list_t *)_node;
    return node->data;
}

void linked_list_destroy(linked_list_t _node)
{
    if (!_node)
        return;
    
    list_t *node = (list_t *)_node;
    if (node->data)
        free(node->data);
    free(node);
}

int linked_list_get_length(linked_list_t _node)
{
    if (!_node)
        return 0;

    list_t *node = (list_t *)_node;
    int cnt = 1;
    while (node->next) {
        node = node->next;
        cnt++;
    }

    return cnt;
}

void linked_list_dump(linked_list_t _node, void (*printFunc)(any_t))
{
    if (!_node || !printFunc)
        return;
    
    list_t *node = (list_t *)_node;
    (*printFunc)(node->data);
}
