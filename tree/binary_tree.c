#include <stdlib.h>
#include <memory.h>
#include "common.h"
#include "tree_impl.h"
#include "queue.h"

#define NODE_INSTANCE(_ptr, node) node_t (node) = (node_t)(_ptr) 

typedef struct _node_t *node_t;
struct _node_t {
    node_t  left;
    node_t  right;
    any_t   data;
};

void *binary_tree_create_node(void *);
void  binary_tree_destroy_node(void *);
void  binary_tree_append_node(void *, void *);
void  binary_tree_dump_node(void *, printFunc);

static tree_impl tree_impl_binary_tree = {
    ._tree_create_node  = binary_tree_create_node,
    ._tree_destroy_node = binary_tree_destroy_node,
    ._tree_append_node  = binary_tree_append_node,
    ._tree_dump_node    = binary_tree_dump_node,
}; 

void *binary_tree_create_node(void *data)
{
    node_t node = calloc(1, sizeof(struct _node_t));
    if (!node)
        return NULL;
    
    node->left  = NULL;
    node->right = NULL;
    node->data  = data;

    return node;
}

void binary_tree_destroy_node(void *_node)
{
    if (!_node)
        return;
    
    NODE_INSTANCE(_node, node);
    node->data  = NULL;
    node->left  = NULL;
    node->right = NULL;
    free(node);
}

static int do_append_node(queue_t q, node_t node)
{
    node_t cur = queue_dequeue(q);
    if (!cur)
        return 0;
    
    if (!cur->left) {
        cur->left = node;
        return 1;
    }

    if (!cur->right) {
        cur->right = node;
        return 1;
    }

    queue_enqueue(q, node->left);
    queue_enqueue(q, node->right);
    return 0;
}

void binary_tree_append_node(void *_cur, void *_node)
{
    if (!_cur || !_node)
        return;
    
    NODE_INSTANCE(_cur, cur);
    NODE_INSTANCE(_node, node);
    queue_t q = queue_create(QUEUE_IMPL_BY_VECTOR, sizeof(node_t), NULL);
    queue_enqueue(q, cur);
    while (!queue_is_empty(q)) {
        int succeed = do_append_node(q, node);
        if (succeed)
            queue_clear(q);
    }
    queue_destroy(q);
}

void binary_tree_dump_node(void *_node, printFunc fn)
{
    if (!_node || !fn)
        return;
    
    (*fn)(_node);
}




