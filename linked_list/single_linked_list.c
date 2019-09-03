#include <stdio.h>
#include <stdlib.h>
#include "single_linked_list.h"

typedef struct single_linked_list single_linked_list;

struct single_linked_list {
    single_linked_list *next;
    any_t               value;
    size_t              size;
};

static single_linked_list *single_linked_list_tail(single_linked_list *node)
{
    if (!node)
        return NULL;
    
    single_linked_list *cur = node;

    while(cur->next)
        cur = cur->next;
    
    return cur;
}

s_llst_t single_linked_list_create(any_t data, size_t size)
{
    single_linked_list *node = calloc(1, sizeof(single_linked_list));
    if (!node)
        return NULL;
    
    node->next  = NULL;
    node->size  = size;
    node->value = calloc(1, size);
    if (!node->value) {
        free(node);
        return NULL;
    }
    memcpy(node->value, data, size);

    return node;
}

void single_linked_list_destroy(s_llst_t _node)
{
    if (!_node)
        return;
    
    single_linked_list *node = (single_linked_list *)_node;
    node->next  = NULL;
    if (node->value)
        free(node->value);
    node->value = NULL;
    free(node);
}

void single_linked_list_append(s_llst_t head, s_llst_t node)
{
    if (!head || !node)
        return;
    
    single_linked_list *tail = single_linked_list_tail((single_linked_list *)head);
    if (!tail)
        return;
    
    tail->next = (single_linked_list *)node;
}

void single_linked_list_delete(s_llst_t head, int idx)
{
    if (idx < 0 || !head)
        return;

    single_linked_list *cur  = (single_linked_list *)head;
    single_linked_list *prev = NULL;
    for (int i = 0; i < idx; i++) {
        if (cur->next) {
            prev = cur;
            cur  = cur->next;
        }
        else
            return;
    }
    prev->next = cur->next;
    single_linked_list_destroy(cur);
    cur = NULL;
}

any_t single_linked_list_get_node(s_llst_t head, int idx)
{
    if (idx < 0 || !head)
        return NULL;
    
    single_linked_list *cur = (single_linked_list *)head;
    for (int i = 0 ; i < idx; i++) {
        if (cur->next) {
            cur = cur->next;
        }
        else
            return NULL;
    }
    return cur;
}

void single_linked_list_dump_node(s_llst_t node, void (*printFunc)(any_t))
{
    (*printFunc)(node);
}

void single_linked_list_iterate(s_llst_t node, PFany func, any_t args)
{
    single_linked_list *cur = (single_linked_list *)node;

    while(cur) {
        (*func)(cur, args);
        cur = cur->next;
    } 
}