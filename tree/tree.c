#include <stdlib.h>
#include <memory.h>
#include "tree.h"
#include "tree_impl.h"

typedef struct tree_node {
    tree_impl *impl;
    void      *instance;
} tree_node;

tree_t tree_create_node(int type, any_t data)
{
    tree_node *node = calloc(1, sizeof(tree_node));
    if (!node)
        return NULL;
    
    node->impl = tree_impl_table[type];
    node->instance = tree_impl_create_node(node->impl, data);
    if (!node->instance) {
        free(node);
        return NULL;
    }

    return node;
}

void tree_destroy_node(tree_t _node)
{
    if (!_node)
        return;
    
    tree_node *node = (tree_node *)_node;
    tree_impl_destroy_node(node->impl, node->instance);
    free(node);
}

void tree_append_node(tree_t _cur, tree_t _node)
{
    if (!_cur || !_node)
        return;
    
    tree_node *cur  = (tree_node *)_cur;
    tree_node *node = (tree_node *)_node;
    tree_impl_append_node(cur->impl, cur->instance, node->instance);
}

void tree_dump_node(tree_t _node)
{
    if (!_node)
        return;
    
    tree_node *node = (tree_node *)_node;
    tree_impl_dump_node(node->impl, node->instance);
}