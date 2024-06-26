#ifndef C_MATRIX_H
#define C_MATRIX_H

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <float.h>
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

    for (int i = 0; i < m.nCols; i++) {
        for (int j = 0; j < m.nRows; j++) {
            if (m.values[j][i] < min) {
                min = m.values[j][i];
                min_position.rowIndex = j;
                min_position.colIndex = i;
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
//1
void swapMinMaxRowsMatrix(matrix *m){
    position min_element = getMinValuePos(*m);
    position max_element = getMaxValuePos(*m);
    if(min_element.rowIndex != max_element.rowIndex)
        swapRows(*m, min_element.rowIndex, max_element.rowIndex);
}

//2
int getMax(int *a, int n){
    int max = a[0];
    for (int i = 1; i < n; i++){
        if (max < a[i])
            max = a[i];
    }

    return max;
}

void sortRowsByMinElement(matrix *m){
    insertionSortRowsMatrixByRowCriteria(*m, getMax);
}

//3
int getMin(int *a, int n){
    int min = a[0];
    for (int i = 1; i < n; i++){
        if (min > a[i])
            min = a[i];
    }

    return min;
}

void sortColsByMinElement(matrix *m) {
    selectionSortColsMatrixByColCriteria(m, getMin);
}

//4
matrix mulMatrices(matrix m1, matrix m2){
    assert(m1.nRows == m2.nCols);
    matrix m3 = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m3.nRows; i++){
        for (int j = 0; j < m3.nCols; j++){
            m3.values[i][j] = 0;
            for (int k = 0; k < m3.nCols; k++)
                m3.values[i][j] += m1.values[i][k] * m2.values[k][j];
        }
    }

    return m3;
}

void getSquareOfMatrixIfSymmetric(matrix *m){
    if(isSymmetricMatrix(m)){
        matrix m1 = mulMatrices(*m, *m);
        freeMemMatrix(m);
        *m = m1;
    }
}

//5
bool isUnique(long long *a, int n){
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if (a[i] == a[j])
                return false;
        }
    }

    return true;
}

long long getSum(int *a, int n){
    long long sum = a[0];
    for (int i = 1; i < n; i++)
        sum += a[i];

    return sum;
}

long long* getArrayOfSum(matrix m){
    long long *a = (long long*) malloc(sizeof(long long) * m.nRows);
    for ( int i = 0; i < m.nRows; i++)
        a[i] = getSum(m.values[i], m.nCols);

    return a;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m){
    if (isUnique(getArrayOfSum(m), m.nRows))
        transposeSquareMatrix(&m);
}

//6
bool isMutuallyInverseMatrices(matrix m1, matrix m2){
    if (m1.nRows != m2.nRows)
        return false;

    matrix one_m = getMemMatrix(m1.nRows, m1.nRows);
    for (int i = 0; i < one_m.nRows; i++) {
        for (int j = 0; j < one_m.nRows; j++)
            one_m.values[i][j] = i == j;
    }

    matrix mul_m = mulMatrices(m1, m2);
    bool res = areTwoMatricesEqual(&one_m, &mul_m);

    freeMemMatrix(&one_m);
    freeMemMatrix(&mul_m);

    return res;
}

//7
int max(int a, int b){
    return a > b ? a : b;
}

int min(int a, int b){
    return a < b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m){
    long diagonal_amount = m.nRows + m.nCols - 2;
    int* max_diagonal_array = (int*) malloc(sizeof(int) * diagonal_amount);
    for (int i = 0; i < diagonal_amount; i++)
        max_diagonal_array[i] = INT_MIN;

    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            if (i == j)
                continue;

            int position = m.nRows - i + j - 1;
            if (position > 2)
                position -= 1;

            max_diagonal_array[position] = max(m.values[i][j], max_diagonal_array[position]);
        }
    }
    long long sum = max_diagonal_array[0];
    for (int i = 1; i < diagonal_amount; i++)
        sum += max_diagonal_array[i];
    free(max_diagonal_array);

    return sum;
}

//8
int getMinInArea(matrix m){
    position max_position = getMaxValuePos(m);
    int min_value = m.values[max_position.rowIndex][max_position.colIndex];

    for (int i = max_position.rowIndex - 1; i >= 0; i--){
        int left_wall = max_position.colIndex - max_position.rowIndex + i;
        int right_wall = max_position.colIndex + max_position.rowIndex - i;
        if (left_wall < 0)
            left_wall = 0;
        if (right_wall > m.nCols - 1)
            right_wall = m.nCols - 1;

        for (int j = left_wall; j <= right_wall; j++) {
            min_value = min(min_value, m.values[i][j]);
        }

    }

    return min_value;
}

//9
bool areSame(double a, double b){
    return fabs(a - b) < DBL_EPSILON;
}

double getDistance(int *a, int n){
    double pre_sqrt = a[0] * a[0];
    for (int i = 1; i < n; i++)
        pre_sqrt += a[i] * a[i];

    return sqrt(pre_sqrt);
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, double (*criteria)(int *, int)){
    for (int i = 1; i < m.nRows ; i++){
        int *temp = m.values[i];
        int j = i;

        while (j > 0 && !areSame(criteria(m.values[j - 1], m.nCols), criteria(temp, m.nCols))) {
            m.values[j] = m.values[j - 1];
            j--;
        }

        m.values[j] = temp;
    }
}

void sortByDistances(matrix m){
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

//10
int cmp_long_long(const void *pa, const void *pb){
    if (pa > pb)
        return 1;
    if (pa < pb)
        return -1;

    return 0;
}

int countNUniqueSorted(long long *a, int n){
    int unique = 0;

    for (int i = 1; i < n; i++){
        if (a[i - 1] == a[i])
            continue;
        unique++;
    }

    return unique;
}

int countEqClassesByRowsSum(matrix m){
    long long *a = getArrayOfSum(m);
    qsort(a, m.nRows, sizeof(long long), cmp_long_long);
    int unique = countNUniqueSorted(a, m.nRows);

    free(a);
    return unique;
}

//11
long long* getArrayOfSumCols(matrix m){
    long long *a = (long long*) malloc(sizeof(long long) * m.nCols);
    for (int i = 0; i < m.nCols; i++)
        a[i] = 0;

    for (int i = 0; i < m.nCols; i++)
        for (int j = 0; j < m.nRows; j++)
            a[i] += (long long) m.values[j][i];

    return a;
}

int getNSpecialElement(matrix m){
    long long *a = getArrayOfSumCols(m);
    int special_number = 0;

    for (int i = 0; i < m.nCols; i++){
        for (int j = 0; j < m.nRows; j++){
            if (m.values[j][i] > a[i] - m.values[j][i]){
                special_number++;
                break;
            }
        }
    }

    free(a);
    return special_number;
}

//12
void swapPenultimateRowWithMinimum(matrix m){
    position min_position = getMinValuePos(m);

    int *min_col_array = (int *) malloc(sizeof(int) * m.nRows);
    for (int i = 0; i < m.nRows; i++)
        min_col_array[i] = m.values[i][min_position.colIndex];

    for (int i = 0; i < m.nCols; i++)
        m.values[m.nRows - 2][i] = min_col_array[i];

    free(min_col_array);
}

//13
bool isNonDescendingSorted(int *a, int n){
    for (int i = 1; i < n; i++){
        if (a[i - 1] > a[i])
            return false;
    }

    return true;
}

bool hasAllNonDescendingRows(matrix m){
    for (int i = 0; i < m.nRows; i++){
        if (!isNonDescendingSorted(m.values[i], m.nCols))
            return false;
    }

    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix){
    int count_nondescending_rows_matrices = 0;
    for (int i = 0; i < nMatrix; i++){
        if (hasAllNonDescendingRows(ms[i]))
            count_nondescending_rows_matrices++;
    }

    return count_nondescending_rows_matrices;
}

//14
int countValues(const int *a, int n, int value){
    int counter = 0;
    for (int i = 0; i < n; i++){
        counter += a[i] == value;
    }

    return counter;
}

int countZeroRows(matrix m){
    int counter = 0;
    for (int i = 0; i < m.nRows; i++){
        if (countValues(m.values[i], m.nCols, 0) == m.nCols)
            counter++;
    }

    return counter;
}

//15
int findNorm(matrix m){
    position min_position = getMinValuePos(m);
    position max_position = getMaxValuePos(m);

    int min_value = m.values[min_position.rowIndex][min_position.colIndex];
    int max_value = m.values[max_position.rowIndex][max_position.colIndex];

    if (min_value < 0)
        min_value *= -1;

    if (max_value < 0)
        max_value *= -1;

    return max_value > min_value ? max_value : min_value;
}

void outputMinNormMatrix(matrix *ms, int nMatrix){
    int min_norm = INT_MAX;
    int min_norm_position = -1;

    for (int i = 0; i < nMatrix; i++){
        int norm = findNorm(ms[i]);

        if(norm < min_norm){
            min_norm = norm;
            min_norm_position = i;
        }
    }

    outputMatrix(ms[min_norm_position]);
}

//16
int getNSpecialElement2(matrix m){
    int counter = 0;

    for (int i = 0; i < m.nRows; i++){
        position max_position = getMaxValuePos(m);

        for (int j = 0 ; j <= max_position.colIndex; j++){
            bool is_special = true;
            for (int k = 0; k < m.nCols; k++){
                if (k < j){
                    if(m.values[i][k] >= m.values[i][j]){
                        is_special = false;
                        break;
                    }
                }
                if (k > j){
                    if(m.values[i][k] <= m.values[i][j]){
                        is_special = false;
                        break;
                    }
                }
            }
            counter += is_special;
        }
    }

    return counter;
}

#endif //C_MATRIX_H