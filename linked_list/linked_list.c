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

/* Operation for list */
linked_list_t linked_list_get_head_node(linked_list_t _node)
{
    if (!_node)
        return NULL;

    list_t *node = (list_t *)_node;
    while(node->prev)
        node = node->prev;

    return node;
}

linked_list_t linked_list_get_tail_node(linked_list_t _node)
{
    if (!_node)
        return NULL;

    list_t *node = (list_t *)_node;
    while(node->next)
        node = node->next;
    
    return node;
}

int linked_list_get_total_length(linked_list_t _node)
{
    list_t *node = (list_t *)_node;
    if (!node)
        return 0;
    int cnt = 1;

    list_t *prev = node->prev;
    list_t *next = node->next;
    while (prev) {
        prev = prev->prev;
        cnt++;
    }
    while (next) {
        next = next->next;
        cnt++;
    }
    return cnt;
}

void linked_list_destroy_list(linked_list_t _node)
{
    if (!_node)
        return;
    list_t *node = (list_t *)_node;
    list_t *next = node->next;
    list_t *prev = node->prev;
    linked_list_destroy(prev);
    linked_list_destroy(next);
}

void linked_list_iterate(linked_list_t _node, PFany fptr, any_t args)
{
    if (!_node || !fptr)
        return;
    
    list_t *node = (list_t *)_node;
    while (node) {
        (*fptr)(node->data, args);
        node = node->next;
    }
}

linked_list_t linked_list_get_node(linked_list_t _node, int idx)
{
    if (!_node || idx < 0)
        return NULL;
    
    list_t *node = (list_t *)_node;
    for (int i = 0 ; i < idx; i++) {
        if (node->next)
            node = node->next;
        else
            return NULL;
    }
    return node;
}

void linked_list_dump_list(linked_list_t _node, void (*printFunc)(any_t))
{
    if (!_node || !printFunc)
        return;
    
    list_t *node = (list_t *)_node;
    while (node) {
        printFunc(node->data);
        node = node->next;
    }
}

linked_list_t linked_list_insert_tail(linked_list_t _list, linked_list_t _node)
{
    if (!_list || !_node)
        return NULL;
    
    list_t *list = (list_t *)_list;
    list_t *node = (list_t *)_node;
    list_t *list_head = list;

    while (list->next)
        list = list->next;
    
    while (list_head->prev)
        list_head = list_head->prev;
    
    list->next = node;
    node->prev = list;

    return list_head;
}

linked_list_t linked_list_insert_head(linked_list_t _list, linked_list_t _node)
{
    if (!_list || !_node)
        return NULL;
    
    list_t *list = (list_t *)_list;
    list_t *node = (list_t *)_node;
    list_t *node_tail = node;
    list_t *node_head = node;

    while (list->prev)
        list = list->prev;

    while (node_tail->next)
        node_tail = node_tail->next;
    
    while (node_head->prev)
        node_head = node_head->prev;
    
    list->prev = node_tail;
    node_tail->next = list;

    return node_head;
}

linked_list_t linked_list_delete_head(linked_list_t _list)
{
    if (!_list)
        return NULL;
    
    list_t *head = linked_list_get_head_node(_list);
    list_t *new_head = head->next;
    linked_list_delete(head);
    return new_head;
}
