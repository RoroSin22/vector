#ifndef C_MATRIX_H
#define C_MATRIX_H

#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m){
    for (int i = 0; i < m->nRows; i++)
        free(m->values[i]);

    m->values = NULL;
    m->nRows = 0;
    m->nCols = 0;
}

void freeMemMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(ms);
}

void inputMatrix(matrix *m){
    for (int i = 0; i < m->nRows; i++){
        for (int j = 0; j < m->nCols; j++)
            scanf("%d", &m->values[i] [j]);
    }
}

void inputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++)
        inputMatrix(&ms[i]);
}

void outputMatrix(matrix m){
    for (int i = 0; i < m.nCols; i++){
        for (int j = 0; j < m.nRows; j++)
            printf("%d ", m.values[i][j]);
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++)
        outputMatrix(ms[i]);
}

void swapRows(matrix m, int i1, int i2){
    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}


#endif //C_MATRIX_H
