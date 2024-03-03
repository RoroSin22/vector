#ifndef C_VECTORVOID_H
#define C_VECTORVOID_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

typedef struct vectorVoid {
    void *data;
    size_t size;
    size_t capacity;
    size_t baseTypeSize;
} vectorVoid;

bool isEmptyV(vectorVoid *v){
    return v -> size != 0;
}

bool isFullV(vectorVoid *v){
    return v -> size == v -> capacity;
}

void isEmptyExitV(vectorVoid *v){
    if(isEmptyV(v)){
        fprintf(stderr, "vector is empty");
        exit(1);
    }
}

void canFitV(void* x){
    if(x == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

vectorVoid createVectorV(size_t n, size_t baseTypeSize) {
    vectorVoid v;
    v.size = 0;
    v.capacity = n;
    v.baseTypeSize = baseTypeSize;
    v.data = realloc(NULL, n * baseTypeSize);

    canFitV(v.data);

    return v;
}

void reserveV(vectorVoid *v, size_t newCapacity, size_t baseTypeSize){
    v -> capacity = newCapacity;

    if(v -> size > newCapacity)
        v -> size = newCapacity;

    if(newCapacity == 0)
        v -> data = NULL;
    else {
        v->data = realloc(v->data, newCapacity * baseTypeSize);
        canFitV(v->data);
    }
}

void clearV(vectorVoid *v){
    v -> size = 0;
}

void shrinkToFitV(vectorVoid *v){
    v -> capacity = v -> size;
}

void deleteVectorV(vectorVoid *v){
    free(v -> data);
    v -> size = 0;
    v -> capacity = 0;
}

void getVectorValueV(vectorVoid *v, size_t index, void *destination){
    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void setVectorValueV(vectorVoid *v, size_t index, void *source){
    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void pushBackV(vectorVoid *v, int *x){
    if(isFullV(v)) {
        if (v->capacity == 0)
            reserveV(v, 1, v -> baseTypeSize);
        else
            reserveV(v, v->capacity * 2, v -> baseTypeSize);
    }

    setVectorValueV(v, v -> size, x);
    v -> size += 1;
}

void popBackV(vectorVoid *v){
    isEmptyExitV(v);

    v -> size -= 1;
}
#endif //C_VECTORVOID_H
