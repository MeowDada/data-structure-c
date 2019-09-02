#ifndef VECTOR_H
#define VECTOR_H

typedef void  *any_t;
typedef void  *vector_t;
typedef void (*PFany)(any_t, any_t);
typedef void (*PrintFunc)(any_t);

extern vector_t   vector_create(void);
extern void       vector_destroy(vector_t *);
extern void       vector_push_back(vector_t, any_t);
extern void       vector_push_front(vector_t, any_t);
extern any_t      vector_pop_back(vector_t);
extern any_t      vector_pop_front(vector_t);
extern any_t      vector_at(vector_t, int);
extern void       vector_clear(vector_t);
extern void       vector_iterate(vector_t, PFany, any_t);
extern void       vector_dump(vector_t, PrintFunc);
extern int        vector_size(vector_t);
extern int        vector_capacity(vector_t);

/* build-in dump function */
extern void vector_print_int(any_t);
extern void vector_print_float(any_t);
extern void vector_print_double(any_t);
extern void vector_print_uint(any_t);
extern void vector_print_long(any_t);
extern void vector_print_long_long(any_t);
extern void vector_print_char(any_t);
extern void vector_print_string(any_t);
extern void vector_print_pointer(any_t);

#endif /* VECTOR_H */