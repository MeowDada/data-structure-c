#ifndef HEAP_H
#define HEAP_H
#include "common.h"

typedef any_t heap_t;

extern heap_t heap_create();
extern void   heap_destroy();
extern void   heap_insert();
extern void   heap_extract();
extern void   heap_find_min();

#endif /* HEAP_H */