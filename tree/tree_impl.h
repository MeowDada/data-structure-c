#ifndef TREE_IMPL_H
#define TREE_IMPL_H
#include "common.h"

typedef struct _tree_impl tree_impl;
struct _tree_impl {
    void *(*_tree_create_node)(void *);
    void  (*_tree_destroy_node)(void *);
    void  (*_tree_append_node)(void *, void *);
    void  (*_tree_dump_node)(void *, printFunc);
};

extern tree_impl tree_impl_binary_tree;
extern tree_impl tree_impl_two_three_tree;
extern tree_impl tree_impl_two_three_four_tree;
extern tree_impl tree_impl_red_black_tree;
extern tree_impl tree_impl_b_tree;
extern tree_impl *tree_impl_table[];

#endif /* TREE_IMPL_H */

