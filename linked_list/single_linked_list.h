#ifndef SINGLE_LINKED_LIST
#define SINGLE_LINKED_LIST
#include "common.h"

typedef any_t s_llst_t;

extern s_llst_t single_linked_list_create(any_t);
extern void     single_linked_list_destroy(s_llst_t);
extern void     single_linked_list_append(s_llst_t, s_llst_t);
extern void     single_linked_list_delete(s_llst_t, int);
extern s_llst_t single_linked_list_get_node(s_llst_t, int);
extern any_t    single_linked_list_get_value(s_llst_t, int);
extern void     single_linked_list_dump_node(s_llst_t, void (*)(any_t));
extern void     single_linked_list_iterate(s_llst_t, PFany, any_t);

#endif /* SINGLE_LINKED_LIST */