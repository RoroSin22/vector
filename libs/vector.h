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

void canFit(void* x){
    if(x == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

vector createVector(size_t n) {
    vector v;
    v.size = 0;
    v.capacity = n;
    v.data = realloc(v.data, n * sizeof(int));

    canFit(v.data);

    return v;
}

void reserve(vector *v, size_t newCapacity){
    v -> capacity = newCapacity;

    if(v -> size < newCapacity)
        v -> size = newCapacity;

    if(newCapacity == 0)
        v -> data = NULL;
    else {
        v->data = realloc(v->data, newCapacity * sizeof(int));
        canFit(v->data);
    }
}

void clear(vector *v){
    v -> size = 0;
}

void shrinkToFit(vector *v){
    v -> capacity = v -> size;
}

void deleteVector(vector *v){
    free(v -> data);
    v -> size = 0;
    v -> capacity = 0;
}

#endif //C_VECTOR_H
