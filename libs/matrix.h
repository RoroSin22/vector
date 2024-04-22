#ifndef C_MATRIX_H
#define C_MATRIX_H

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "array.h"

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
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++)
        outputMatrix(ms[i]);
}

void swapElements(matrix m, int i1, int j1, int i2, int j2){
    int temp = m.values[i1][j1];
    m.values[i1][j1] = m.values[i2][j2];
    m.values[i2][j2] = temp;
}

void swapRows(matrix m, int i1, int i2){
    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}

void swapColumns(matrix m, int j1, int j2){
    for (int i = 0; i < m.nRows; i++){
        int temp = m.values[i] [j1];
        m.values[i] [j1] = m.values[i] [j2];
        m.values[i] [j2] = temp;
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)){
    for (int i = 1; i < m.nRows ; i++){
        int *temp = m.values[i];
        int j = i;

        while (j > 0 && criteria(m.values[j - 1], m.nCols) > criteria(temp, m.nCols)) {
            m.values[j] = m.values[j - 1];
            j--;
        }

        m.values[j] = temp;
    }
}

void selectionSortColsMatrixByColCriteria(matrix *m, int (*criteria)(int *,int)) {
    int temp[m->nCols];

    for (int i = 0; i < m->nCols; i++) {
        int temp_column[m->nRows];

        for (int j = 0; j < m->nRows; j++)
            temp_column[j] = m->values[j][i];

        int result = criteria(temp_column, m->nCols);
        temp[i] = result;
    }

    int min_position;
    int temp_position;

    for (int i = 0; i < m->nCols; i++) {
        min_position = i;
        for (int j = i + 1; j < m->nCols; j++)
            if (temp[min_position] > temp[j])
                min_position = j;
        temp_position = temp[min_position];
        temp[min_position] = temp[i];
        temp[i] = temp_position;
        swapColumns(*m, min_position, i);
    }
}


bool isSquareMatrix(matrix *m){
    return m->nCols == m->nRows;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2){
    if (m1->nCols != m2->nCols && m1->nRows != m2->nRows)
        return false;

    for (int i = 0; i < m1->nRows; i++){
        if (memcmp(m1->values[i], m2->values[i], sizeof(int) * m1->nCols) != 0)
            return false;
    }

    return true;
}

bool onlyNotZeroAtRow(int *r, int length, int position){
    for(int i = 0; i < length; i++){
        if(r[i] != 0 && i != position)
            return false;
    }

    return true;
}

bool isEMatrix(matrix *m){
    if (!isSquareMatrix(m))
        return 0;

    for (int i = 0; i < m->nRows; i++){
        if (!onlyNotZeroAtRow(m->values[i], m->nCols, i))
            return false;
    }

    return true;
}

bool isSymmetricMatrix(matrix *m){
    if (!isSquareMatrix(m))
        return false;
    if (m->nRows == 1)
        return true;

    for (int i = 0; i < m->nRows; i++){
        for (int j = 0; j < i; j++) {
            if (i == j)
                continue;

            if (m->values[i][j] != m->values[j][i])
                return false;
        }
    }

    return true;
}

void transposeSquareMatrix(matrix *m) {
    if (isSymmetricMatrix(m))
        return;

    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            swapElements(*m, i, j, j, i);
        }
    }
}

void transposeMatrix(matrix *m){
    matrix transposed = getMemMatrix(m->nCols, m->nRows);
    for (int i = 0; i < m->nRows; i++){
        for (int j = 0; j < m->nCols; j++)
            transposed.values[j][i] = m->values[i][j];
    }

    freeMemMatrix(m);
    *m = getMemMatrix(transposed.nRows,transposed.nCols);
    m->nRows = transposed.nRows;
    m->nCols = transposed.nCols;

    for(int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++)
            m->values[i][j] = transposed.values[i][j];
    }

    freeMemMatrix(&transposed);
}

position getMinValuePos(matrix m){
    int min = m.values[0][0];
    position min_position = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                min_position.rowIndex = i;
                min_position.colIndex = j;
            }
        }
    }

    return min_position;
}

position getMaxValuePos(matrix m) {
    int max = m.values[0][0];
    position max_position = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                max_position.rowIndex = i;
                max_position.colIndex = j;
            }
        }
    }

    return max_position;
}

//for tests
matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;

    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows,size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;

    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}

//Lab work 17

void swapMinMaxRowsMatrix(matrix *m){
    position min_element = getMinValuePos(*m);
    position max_element = getMaxValuePos(*m);
    if(min_element.rowIndex != max_element.rowIndex)
        swapRows(*m, min_element.rowIndex, max_element.rowIndex);
}

#endif //C_MATRIX_H
