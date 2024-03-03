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

bool isEmpty(vector *v){
    return v -> size != 0;
}

bool isFull(vector *v){
    return v -> size == v -> capacity;
}

void isEmptyExit(vector *v){
    if(isEmpty(v)){
        fprintf(stderr, "vector is empty");
        exit(1);
    }
}

void isOutOFRangeExit(vector *v, size_t index){
    if(v -> size <= index){
        fprintf(stderr, "IndexError: a[%lld] is not exists", index);
        exit(1);
    }
}

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
    v.data = realloc(NULL, n * sizeof(int));

    canFit(v.data);

    return v;
}

void reserve(vector *v, size_t newCapacity){
    v -> capacity = newCapacity;

    if(v -> size > newCapacity)
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

int getVectorValue(vector *v, size_t i){
    return v -> data[i];
}

void pushBack(vector *v, int x){
    if(isFull(v)) {
        if (v->capacity == 0)
            reserve(v, 1);
        else
            reserve(v, v->capacity * 2);
    }

    v -> data[v -> size] = x;
    v -> size += 1;
}

void popBack(vector *v){
    isEmptyExit(v);

    v -> size -= 1;
}

int* atVector(vector *v, size_t index){
    isOutOFRangeExit(v, index);

    return &(v -> data[index]);
}

int* back(vector *v){
    isOutOFRangeExit(v, 0);

    return &(v -> data[v -> size - 1]);
}

int* front(vector *v){
    isOutOFRangeExit(v, 0);

    return &(v -> data[0]);
}

#endif //C_VECTOR_H
