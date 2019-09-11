#include "tree_impl.h"
#include "tree_type.h"

tree_impl *tree_impl_table[] = {
    [BINARY_TREE]         = &tree_impl_binary_tree,
    [TWO_THREE_TREE]      = &tree_impl_two_three_tree,
    [TWO_THREE_FOUR_TREE] = &tree_impl_two_three_four_tree,
    [RED_BLACK_TREE]      = &tree_impl_red_black_tree,
    [B_TREE]              = &tree_impl_b_tree,
};