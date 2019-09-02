#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define VECTOR_INIT_CAPACITY (1)
#define VECTOR_RESIZE_FACTOR (2)
#define VECTOR_RESIZE_RATIO  ((VECTOR_RESIZE_FACTOR)*(VECTOR_RESIZE_FACTOR))
#define VECTOR_GET_INSTANCE vector *vec = (vector *)v;

typedef struct vector {
    any_t  *data;
    int     size;
    int     capacity;
} vector;

static inline any_t vector_last_index(vector *v)
{
    return v->data[v->size-1];
}

static void vector_resize_bigger(vector *v)
{
    v->capacity = v->capacity * VECTOR_RESIZE_FACTOR;
    any_t temp = realloc(v->data, v->capacity * sizeof(any_t));
    if (temp)
        v->data = (any_t *)temp;
}

static void vector_resize_smaller(vector *v)
{
    v->capacity = v->capacity / VECTOR_RESIZE_FACTOR;
    any_t temp = realloc(v->data, v->capacity * sizeof(any_t));
    if (temp)
        v->data = (any_t *)temp;
}

static void vector_resize_check(vector *vec)
{
    if (vec->capacity <= vec->size)
        return;

    if (vec->capacity == vec->size)
        vector_resize_bigger(vec);
    else if(vec->size == vec->capacity / VECTOR_RESIZE_RATIO)
        vector_resize_smaller(vec);
}

static void vector_remove_element(vector *v, int idx)
{
    if (idx >= v->size || idx < 0)
        return;
    
    int size = v->size;
    for (int i = idx; i < size-1; i++)
        v->data[i] = v->data[i+1];
    v->data[size-1] = NULL;
    v->size--;
}

vector_t vector_create(void)
{
    vector *vec = calloc(1, sizeof(vector));
    if (!vec)
        return NULL;
    
    vec->capacity = VECTOR_INIT_CAPACITY;
    vec->size     = 0;
    vec->data     = calloc(vec->capacity, sizeof(void *));
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
    
    vector *vec = *v;
    free(vec->data);
    free(vec);
    *v = NULL;
}

void vector_push_back(vector_t v, any_t element)
{
    vector_resize_check(v);
    
    VECTOR_GET_INSTANCE
    vec->data[vec->size] = element;
    vec->size++;
}

void vector_push_front(vector_t v, any_t element)
{
    vector_resize_check(v);

    VECTOR_GET_INSTANCE
    int size = vec->size;
    for (int i = 0 ; i < size; i++)
        vec->data[size-i] = vec->data[size-i];
    vec->data[0] = element;
    vec->size++;
}

any_t vector_pop_back(vector_t v)
{
    VECTOR_GET_INSTANCE
    if (vec->size <= 0)
        return NULL;
    
    any_t elem = vec->data[vec->size-1];
    vector_remove_element(vec, vec->size-1);
    vector_resize_check(vec);
    return elem;
}

any_t vector_pop_front(vector_t v)
{
    VECTOR_GET_INSTANCE
    if (vec->size <= 0)
        return NULL;
    
    any_t elem = vec->data[0];
    vector_remove_element(vec, 0);
    vector_resize_check(vec);
    return elem;
}

any_t vector_at(vector_t v, int idx)
{
    VECTOR_GET_INSTANCE
    if (idx < 0 || idx > vec->size)
        return NULL;
    
    return vec->data[idx];
}

void vector_clear(vector_t v)
{
    VECTOR_GET_INSTANCE
    for (int i = 0; i < vec->size; i++)
        vec->data[i] = NULL;
    vec->size = 0;
}

void vector_iterate(vector_t v, PFany fptr, any_t args)
{
    VECTOR_GET_INSTANCE
    if (!vec || !fptr)
        return;
    
    int size = vec->size;
    for (int i = 0; i < size; i++) {
        (*fptr)(v, args);
    }
}

void vector_dump(vector_t v, PrintFunc fptr)
{
    if (!v || !fptr)
        return;
    
    VECTOR_GET_INSTANCE
    int size = vec->size;
    for (int i = 0; i < size; i++)
        (*fptr)(vec->data[i]);
    printf("\n");
}

void vector_info(vector_t v)
{
    VECTOR_GET_INSTANCE

    if (!v) {
        printf("vector is (nil)\n");
        return;
    }

    printf("%-12s = %p\n", "vector pos", vec);
    if (vec->data)
        printf("%-12s = %p\n", "vector data", vec->data);
    else
        printf("%-12s = (nil)\n", "vector data");
    printf("%-12s = %d\n", "vector size", vec->size);
    printf("%-12s = %d\n", "vector capacity", vec->capacity);
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

