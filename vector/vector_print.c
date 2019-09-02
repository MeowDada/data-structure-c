#include <stdio.h>
#include "vector.h"

#define PRINT_NULL "(nil)"

void vector_print_int(any_t data)
{
    if (!data)
        printf("%s ", PRINT_NULL);
    else
        printf("%d ", *(int *)data);
}

void vector_print_float(any_t data)
{
    if (!data)
        printf("%s ", PRINT_NULL);
    else
        printf("%f ", *(float *)data);
}

void vector_print_double(any_t data)
{
    if (!data)
        printf("%s ", PRINT_NULL);
    else
        printf("%lf ", *(double *)data);
}

void vector_print_uint(any_t data)
{
    if (!data)
        printf("%s ", PRINT_NULL);
    else
        printf("%u ", *(unsigned int *)data);
}

void vector_print_long(any_t data)
{
    if (!data)
        printf("%s ", PRINT_NULL);
    else
        printf("%ld ", *(long *)data);
}

void vector_print_long_long(any_t data)
{
    if (!data)
        printf("%s ", PRINT_NULL);
    else
        printf("%lld ", *(long long *)data);
}

void vector_print_char(any_t data)
{
    if (!data)
        printf("%s ", PRINT_NULL);
    else
        printf("%c ", *(char *)data);
}

void vector_print_string(any_t data)
{
    if (!data)
        printf("%s ", PRINT_NULL);
    else
        printf("%s ", (char *)data);
}

void vector_print_pointer(any_t data)
{
    if (!data)
        printf("%s ", PRINT_NULL);
    else
        printf("%p ", data);
}