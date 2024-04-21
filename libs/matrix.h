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

/*int getTempCols(matrix m, int cols){
    int *temp = (int *) malloc(sizeof(int) * m.nCols);
    for (int i = 0; i < m.nCols; i++)
        temp[i] = m.values[cols] [i];

    return *temp;
}

void switchCols(matrix *m, int col_number, int *second_col){
    for (int i = 0; i < m->nRows; i++)
        m->values[i] [col_number] = second_col[i];
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)){
    for (int i = 0; i < m.nCols; i++){
        int temp = getTempCols(m, i);
        int j = i;

        while (j > 0 && criteria(m.values[j - 1], m.nCols) > criteria(&temp, m.nCols)) {
            switchCols(m, j, m.values[])
            j--;
        }
    }
} */

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

    for (int i = 0; i < m->nRows / 2 + m->nRows % 2; i++){
        for (int j = 0; j < m->nCols / 2 + m->nCols % 2; j++) {
            if (i == j)
                continue;

            if (m->values[i][j] != m->values[j][i])
                return false;
        }
    }

    return true;
}

#endif //C_MATRIX_H
