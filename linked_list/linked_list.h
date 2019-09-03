#ifndef LINKED_LIST
#define LINKED_LIST
#include "common.h"

typedef any_t linked_list_t;

/* operation for single linked list node */
extern linked_list_t linked_list_create(any_t, size_t);
extern void          linked_list_append(linked_list_t, linked_list_t);
extern void          linked_list_delete(linked_list_t);
extern any_t         linked_list_get_value(linked_list_t);
extern void          linked_list_destroy(linked_list_t);
extern int           linked_list_get_length(linked_list_t);
extern void          linked_list_dump(linked_list_t, void (*)(any_t));

/* operations for the whole linked list */
extern int           linked_list_get_total_length(linked_list_t);
extern void          linked_list_destroy_list(linked_list_t);
extern void          linked_list_iterate(linked_list_t, PFany, any_t);
extern linked_list_t linked_list_get_node(linked_list_t, int);
extern void          linked_list_dump_list(linked_list_t, void (*)(any_t));
extern linked_list_t linked_list_insert_tail(linked_list_t, linked_list_t);
extern linked_list_t linked_list_insert_front(linked_list_t, linked_list_t);

#endif /* LINKED_LIST */