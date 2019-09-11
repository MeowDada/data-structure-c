#ifndef TREE_H
#define TREE_H
#include "common.h"

typedef any_t tree_t;

extern tree_t tree_create_node(any_t);
extern void   tree_destroy_node(tree_t);
extern void   tree_append_node(tree_t, tree_t);
extern void   tree_dump_node(tree_t);

#endif /* TREE_H */