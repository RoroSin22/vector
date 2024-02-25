
#ifndef C_VECTOR_H
#define C_VECTOR_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>

typedef struct vector {
    int *data;
    size_t size;
    size_t capacity;
} vector;

#endif //C_VECTOR_H
