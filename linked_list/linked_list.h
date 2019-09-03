#ifndef LINKED_LIST
#define LINKED_LIST
#include "common.h"

typedef any_t linked_list_t;
typedef any_t linked_list_node_t;

extern void  linked_list_create_node(any_t);
extern void  linked_list_append_node(linked_list_t, linked_list_node_t);
extern void  linked_list_delete_node(linked_list_node_t);
extern any_t linked_list_get_node_value(linked_list_node_t);
extern void  linked_list_destroy_node(linked_list_node_t);
extern void  linked_list_iterate(linked_list_t, FPany);
extern int   linked_list_get_length(linked_list_node_t);
extern void  linked_list_dump_node(linked_list_node_t);

#endif /* LINKED_LIST */