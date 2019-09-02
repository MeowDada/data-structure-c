#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "vector.h"

#define VECTOR_INIT_CAPACITY (1)
#define VECTOR_RESIZE_FACTOR (2)
#define VECTOR_RESIZE_RATIO  ((VECTOR_RESIZE_FACTOR)*(VECTOR_RESIZE_FACTOR))
#define VECTOR_GET_INSTANCE vector *vec = (vector *)v;
#define VEC(i) (void *)((char *)vec->data + vec->sizeof_elem*i)

typedef struct vector {
    any_t  *data;
    int     size;
    int     capacity;
    size_t  sizeof_elem;
} vector;

static int vector_validate_index(vector *vec, int idx)
{
    if (vec->size == 0 || vec->size <= idx || idx < 0)
        return -1;
    return 0;
}

static any_t vector_copy_element(void *elem, size_t size)
{
    any_t temp = calloc(1, size);
    memcpy(temp, elem, size);
    return temp;
}

static void vector_assign_element(vector *vec, int idx, any_t data)
{
    if (idx < 0 || idx > vec->size)
        return;
    
    memcpy(VEC(idx), data, vec->sizeof_elem);
}

static void vector_assign_value(vector *vec, int from, int to)
{
    any_t elem_from = VEC(from);
    any_t elem_to   = VEC(to);
    memcpy(elem_to, elem_from, vec->sizeof_elem);
}

static void vector_shift_element(vector *vec, int pos, int offset)
{
    if (pos+offset < 0 || pos < 0 || pos >= vec->capacity || pos+offset >= vec->capacity)
        return;
    
    size_t bytes_to_shift = offset > 0 ? offset*vec->sizeof_elem : -offset*vec->sizeof_elem;
    memmove(VEC(pos+offset), VEC(pos), bytes_to_shift);
}

static void vector_clear_element(vector *vec, int idx)
{
    if (vector_validate_index(vec, idx))
        return;
    
    memset(VEC(idx), 0, vec->sizeof_elem);
}

static void vector_resize_bigger(vector *vec)
{
    vec->capacity = vec->capacity * VECTOR_RESIZE_FACTOR;
    any_t temp = realloc(vec->data, vec->capacity * vec->sizeof_elem);
    if (temp)
        vec->data = (any_t *)temp;
}

static void vector_resize_smaller(vector *vec)
{
    vec->capacity = vec->capacity / VECTOR_RESIZE_FACTOR;
    any_t temp = realloc(vec->data, vec->capacity * vec->sizeof_elem);
    if (temp)
        vec->data = (any_t *)temp;
}

static void vector_resize_check(vector *vec)
{
    if (vec->capacity == vec->size)
        vector_resize_bigger(vec);
    else if(vec->size == vec->capacity / VECTOR_RESIZE_RATIO &&
            vec->capacity > VECTOR_INIT_CAPACITY)
        vector_resize_smaller(vec);
}

static void vector_remove_element(vector *vec, int idx)
{
    if(vector_validate_index(vec, idx))
        return;
    
    int tail = vec->size-1;
    int diff = tail-idx;

    if (diff > 0)
        memmove(VEC(idx), VEC(idx+1), diff*vec->sizeof_elem);
    else if(diff == 0)
        vector_clear_element(vec, 0);
    vec->size--;
}

vector_t vector_create(size_t size)
{
    vector *vec = calloc(1, sizeof(vector));
    if (!vec)
        return NULL;
    
    vec->capacity    = VECTOR_INIT_CAPACITY;
    vec->size        = 0;
    vec->sizeof_elem = size;
    vec->data        = calloc(vec->capacity, size);
    if (!vec->data) {
        free(vec);
        return NULL;
    }
    return (vector_t)vec;
}

void vector_destroy(vector_t *v)
{
    if (!v || !*v)
        return;
    
    vector *vec = (vector *)*v;
    if (vec->data)
        free(vec->data);
    free(vec);
    *v = NULL;
}

void vector_push_back(vector_t v, any_t element)
{
    vector_resize_check(v);
    
    VECTOR_GET_INSTANCE
    vector_assign_element(vec, vec->size, element);
    vec->size++;
}

void vector_push_front(vector_t v, any_t element)
{
    vector_resize_check(v);

    VECTOR_GET_INSTANCE
    int size = vec->size;
    
    vector_shift_element(vec, 0, 1);
    vector_assign_element(vec, 0, element);
    vec->size++;
}

any_t vector_pop_back(vector_t v)
{
    VECTOR_GET_INSTANCE
    if (vec->size <= 0)
        return NULL;
    
    any_t elem = vector_copy_element(VEC(vec->size-1), vec->sizeof_elem);
    vector_remove_element(vec, vec->size-1);
    vector_resize_check(vec);
    return elem;
}

any_t vector_pop_front(vector_t v)
{
    VECTOR_GET_INSTANCE
    if (vec->size <= 0)
        return NULL;
    
    any_t elem = vector_copy_element(VEC(0), vec->sizeof_elem);
    vector_remove_element(vec, 0);
    vector_resize_check(vec);
    return elem;
}

any_t vector_at(vector_t v, int idx)
{
    VECTOR_GET_INSTANCE
    if (vector_validate_index(vec, idx))
        return NULL;
    
    return VEC(idx);
}

void vector_clear(vector_t v)
{
    VECTOR_GET_INSTANCE
    memset(vec->data, 0, vec->capacity*vec->sizeof_elem);
    vec->size = 0;
}

void vector_iterate(vector_t v, PFany fptr, any_t args)
{
    VECTOR_GET_INSTANCE
    if (!vec || !fptr)
        return;
    
    int size = vec->size;
    for (int i = 0; i < size; i++) {
        (*fptr)(VEC(i), args);
    }
}

void vector_sort(vector_t v, PsortFunc sort_func, size_t num, size_t size, cmpFunc cmp)
{
    if (!v || !sort_func)
        return;
    
    VECTOR_GET_INSTANCE
    (*sort_func)(vec->data, num, size, cmp);
}

void vector_dump(vector_t v, PrintFunc fptr)
{
    if (!v || !fptr)
        return;
    
    VECTOR_GET_INSTANCE
    int size = vec->size;
    for (int i = 0; i < size; i++)
        (*fptr)(VEC(i));
    printf("\n");
}

void vector_info(vector_t v)
{
    VECTOR_GET_INSTANCE

    if (!v) {
        printf("vector is (nil)\n");
        return;
    }

    printf("%-16s = %p\n", "vector pos", vec);
    if (vec->data)
        printf("%-16s = %p\n", "vector data", vec->data);
    else
        printf("%-16s = (nil)\n", "vector data");
    printf("%-16s = %d\n", "vector size", vec->size);
    printf("%-16s = %d\n", "vector capacity", vec->capacity);
}

int vector_size(vector_t v)
{
    VECTOR_GET_INSTANCE
    return (int)vec->size;
}

int vector_capacity(vector_t v)
{
    VECTOR_GET_INSTANCE
    return (int)vec->capacity;
}

