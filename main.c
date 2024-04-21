#include <stdio.h>
#include <stdbool.h>
#include "libs/matrix.h"
#include <assert.h>

int getSum(int *a, int length){
    int sum = a[0];

    for (int i = 1; i < length; i++)
        sum += a[i];

    return sum;
}

void test_getMemMatrix() {
    matrix m = getMemMatrix(2, 2);
    assert(m.nCols == 2 && m.nRows == 2);
    // проверка выделения памяти
    assert(m.values != NULL);
    freeMemMatrix(&m);
    // проверка на других входных данных
    m = getMemMatrix(2, 9);
    assert(m.nCols == 9 && m.nRows == 2);
    assert(m.values != NULL);
    //освобождаем память
    freeMemMatrix(&m);
}
void test_getMemArrayOfMatrices() {
    matrix *ms = getMemArrayOfMatrices(2, 2, 2);
    // проверка на данные о колоннах и столбцах
    assert(ms->nCols == 2 && ms->nRows == 2);
    //проверка выделения памяти
    assert(ms != NULL);
    freeMemMatrices(ms, 2);
    ms = getMemArrayOfMatrices(9, 5, 2);
    // проверка на данные о колоннах и столбцах
    assert(ms->nCols == 2 && ms->nRows == 5);
    // проверка выделения памяти
    assert(ms != NULL);
    freeMemMatrices(ms, 2);
}
void test_freeMemMatrix() {
    // создаем и чистим массив
    matrix m = getMemMatrix(2, 2);
    freeMemMatrix(&m);
    assert(m.values == NULL);
    //проверка на других данных
    m = getMemMatrix(3, 6);
    freeMemMatrix(&m);
    assert(m.values == NULL);
}

void test_swapRows() {
    // исходная матрица
    matrix m = createMatrixFromArray((int[])
                                             {4, 5, 6,
                                              1, 2, 3,},
                                     2, 3);
    // проверочная матрица
    matrix exp_res = createMatrixFromArray((int[]) {
                                                   1, 2, 3,
                                                   4, 5, 6},
                                           2, 3);
    swapRows(m, 0, 1);
    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}
void test_swapColumns() {
    // исходная матрица
    matrix m = createMatrixFromArray((int[]) {
                                             4, 5, 6,
                                             1, 2, 3,},
                                     2, 3);
    // проверочная матрица
    matrix exp_res = createMatrixFromArray((int[]) {
                                                   5, 4, 6,
                                                   2, 1, 3,},
                                           2, 3);
    swapColumns(m, 0, 1);
    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}
void test_insertionSortRowsMatrixByRowCriteria() {
    //исходная матрица
    matrix m = createMatrixFromArray((int[]) {
                                             3, 3, 3,
                                             1, 1, 1,},
                                     2, 3);
    //проверочная матрица
    matrix exp_res = createMatrixFromArray((int[]) {
                                                   1, 1, 1,
                                                   3, 3, 3,},
                                           2, 3);
    insertionSortRowsMatrixByRowCriteria(m, getSum);
    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}
void test_selectionSortColsMatrixByColCriteria() {
    // исходная матрица
    matrix m = createMatrixFromArray((int[]) {
                                             1, 3, 1,
                                             1, 3, 1,},
                                     2, 3);
    // проверочная матрица
    matrix exp_res = createMatrixFromArray((int[]) {
                                                   1, 1, 3,
                                                   1, 1, 3,},
                                           2, 3);
    selectionSortColsMatrixByColCriteria(&m, getSum);
    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}
void test_isSquareMatrix() {
    //проверка квадратной матрицы
    matrix m = getMemMatrix(4, 4);
    assert(isSquareMatrix(&m));
    freeMemMatrix(&m);
    // проверка с не квадратной матрицей
    m = getMemMatrix(5, 8);
    assert(!isSquareMatrix(&m));
    freeMemMatrix(&m);
}
void test_areTwoMatricesEqual() {
    matrix m = createMatrixFromArray((int[]) {
                                             5, 4, 3,
                                             2, 1, 0,},
                                     2, 3);
    matrix exp_res = createMatrixFromArray((int[]) {
                                                   5, 4, 3,
                                                   2, 1, 0,},
                                           2, 3);
    //матрицы равны
    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
    m = createMatrixFromArray((int[]) {
                                      1, 3, 1,
                                      1, 3, 3,},
                              2, 3);
    exp_res = createMatrixFromArray((int[]) {
                                            8, 6, 4,
                                            2, 3, 3,},
                                    2, 3);
    //матрицы не равны
    assert(!areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}
void test_isEMatrix() {
    matrix m = createMatrixFromArray((int[]) {
                                             1, 0, 0,
                                             0, 1, 0,
                                             0, 0, 1},
                                     3, 3);
    assert(isEMatrix(&m));
    matrix m_1 = createMatrixFromArray((int[]) {
                                               0, 1, 0,
                                               0, 1, 0,
                                               0, 1, 0},
                                       3, 3);
    assert(isEMatrix(&m_1) == 0);
}
void test_isSymmetricMatrix() {
    matrix m = createMatrixFromArray((int[]) {
                                             1, 0, 0,
                                             0, 1, 0,
                                             0, 0, 1},
                                     3, 3);
    assert(isSymmetricMatrix(&m));
    matrix m_1 = createMatrixFromArray((int[]) {
                                               1, 0, 0,
                                               0, 1, 0},
                                       2, 3);
    assert(isSymmetricMatrix(&m_1) == 0);
}
void test_transposeSquareMatrix() {
    matrix m = createMatrixFromArray((int[]) {
                                             1, 2, 3,
                                             4, 5, 0,
                                             -1, 3, 4},
                                     3, 3);
    matrix exp_res = createMatrixFromArray((int[]) {
                                                   1, 4, -1,
                                                   2, 5, 3,
                                                   3, 0, 4},
                                           3, 3);
    transposeSquareMatrix(&m);
    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}
void test_transposeMatrix() {
    matrix m = createMatrixFromArray((int[]) {
                                             1, 2, 3,
                                             4, 5, 6,},
                                     2, 3);
    matrix exp_res = createMatrixFromArray((int[]) {
                                                   1, 4,2,
                                                   5,3, 6,},
                                           3, 2);
    transposeMatrix(&m);
    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}
void test_getMinValuePos() {
    //нахождение минимума
    matrix m = createMatrixFromArray((int[]) {
                                             -1, 6, 3,
                                             18, 7, 0,},
                                     2, 3);
    position p = getMinValuePos(m);
    assert(p.rowIndex == 0 && p.colIndex == 0);
    freeMemMatrix(&m);
}
void test_getMaxValuePos() {
    //нахождение максимума
    matrix m = createMatrixFromArray((int[]) {
                                             11, 10, 10,
                                             4, 15, 12,},
                                     2, 3);
    position p1 = getMaxValuePos(m);
    assert(p1.rowIndex == 1 && p1.colIndex == 1);
    freeMemMatrix(&m);
}
void test() {
    //тесты взаимодействия с памятью
    test_getMemMatrix();
    test_getMemArrayOfMatrices();
    test_freeMemMatrix();
    //тест перераспределяющих функций
    test_swapRows();
    test_swapColumns();
    //тест для упорядочивания строк и столбцов
    test_insertionSortRowsMatrixByRowCriteria();
    test_selectionSortColsMatrixByColCriteria();
    //тесты функций-предикаты
    test_isSquareMatrix();
    test_areTwoMatricesEqual();
    test_isEMatrix();
    test_isSymmetricMatrix();
    //тесты функций преобразования матриц
    test_transposeSquareMatrix();
    test_transposeMatrix();
    //тест функции для поиска минимального и макcимального элемента матрицы
    test_getMinValuePos();
    test_getMaxValuePos();
}

int main() {
    test();

    return 0;
}