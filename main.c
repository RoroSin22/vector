#include <stdio.h>
#include <stdbool.h>
#include "libs/matrix.h"
#include <assert.h>

void test_swapMinMaxRowsMatrix() {
    //стандартный (простой) запуск функци
    matrix m1 = createMatrixFromArray((int[]) {
                                             1, 2, 3,
                                             4, 5, 6,
                                             7, 8,  9,},
                                     3, 3);
    swapMinMaxRowsMatrix(&m1);

    matrix exp_res1 = createMatrixFromArray((int[]) {
                                                   7, 8, 9,
                                                   4, 5, 6,
                                                   1, 2,  3,},
                                           3, 3);
    assert(areTwoMatricesEqual(&m1, &exp_res1));
    freeMemMatrix(&m1);
    freeMemMatrix(&exp_res1);

    //минимальное и максимальное значание находиться в одной строке
    matrix m2 = createMatrixFromArray((int[]) {
                                             0, 2, 19,
                                             4, 5, 6,
                                             1, 8,  7,},
                                     3, 3);
    swapMinMaxRowsMatrix(&m2);

    matrix exp_res2 = createMatrixFromArray((int[]) {
                                                    0, 2, 19,
                                                    4, 5, 6,
                                                    1, 8,  7,},
                                            3, 3);
    assert(areTwoMatricesEqual(&m2, &exp_res2));
    freeMemMatrix(&m2);
    freeMemMatrix(&exp_res2);

    //размеры nRows и nCols равны 1
    matrix m3 = createMatrixFromArray((int[]) {
                                              1,},
                                      1, 1);
    swapMinMaxRowsMatrix(&m3);

    matrix exp_res3 = createMatrixFromArray((int[]) {
                                                    1},
                                            1, 1);
    assert(areTwoMatricesEqual(&m3, &exp_res3));
    freeMemMatrix(&m3);
    freeMemMatrix(&exp_res3);
}

void test_sortRowsByMinElement() {
    //стандартный (простой) запуск функци
    matrix m1 = createMatrixFromArray((int[]) {
                                              7, 1, 2,
                                              1, 8, 1,
                                              3, 2,  3,},
                                      3, 3);

    sortRowsByMinElement(&m1);

    matrix exp_res1 = createMatrixFromArray((int[]) {
                                                    3, 2, 3,
                                                    7, 1, 2,
                                                    1, 8,  1,},
                                            3, 3);
    assert(areTwoMatricesEqual(&m1, &exp_res1));
    freeMemMatrix(&m1);
    freeMemMatrix(&exp_res1);

    //Матрица отсортирована в обратном порядке
    matrix m2 = createMatrixFromArray((int[]) {
                                              0, 2, 19,
                                              4, 15, 6,
                                              1, 8,  7,},
                                      3, 3);
    sortRowsByMinElement(&m2);

    matrix exp_res2 = createMatrixFromArray((int[]) {
                                                    1, 8, 7,
                                                    4, 15, 6,
                                                    0, 2,  19,},
                                            3, 3);
    assert(areTwoMatricesEqual(&m2, &exp_res2));
    freeMemMatrix(&m2);
    freeMemMatrix(&exp_res2);

    //все элементы матрицы равны 0
    matrix m3 = createMatrixFromArray((int[]) {
                                              0, 0, 0,
                                              0, 0, 0,
                                              0, 0,  0,},
                                      3, 3);
    sortRowsByMinElement(&m3);

    matrix exp_res3 = createMatrixFromArray((int[]) {
                                                    0, 0, 0,
                                                    0, 0, 0,
                                                    0, 0,  0,},
                                            3, 3);
    assert(areTwoMatricesEqual(&m3, &exp_res3));
    freeMemMatrix(&m3);
    freeMemMatrix(&exp_res3);
}

void test_sortColsByMinElement() {
    //стандартный (простой) запуск функци
    matrix m1 = createMatrixFromArray((int[]) {
                                              3,5,2,4,3,3,
                                              2,5,1,8,2,7,
                                              6,1,4,4,8,3},
                                      3, 6);

    sortColsByMinElement(&m1);

    matrix exp_res1 = createMatrixFromArray((int[]) {
                                                    5,2,3,3,3,4,
                                                    5,1,2,2,7,8,
                                                    1,4,6,8,3,4},
                                            3, 6);
    assert(areTwoMatricesEqual(&m1, &exp_res1));
    freeMemMatrix(&m1);
    freeMemMatrix(&exp_res1);

    //Матрица отсортирована в обратном порядке
    matrix m2 = createMatrixFromArray((int[]) {
                                              9,8,7,6,33,4,
                                              9,17,23,23,74,83,
                                              9,45,62,82,5,4},
                                      3, 6);
    sortColsByMinElement(&m2);

    matrix exp_res2 = createMatrixFromArray((int[]) {
                                                    4,33,6,7,8,9,
                                                    83,74,23,23,17,9,
                                                    4,5,82,62,45,9},
                                            3, 6);
    assert(areTwoMatricesEqual(&m2, &exp_res2));
    freeMemMatrix(&m2);
    freeMemMatrix(&exp_res2);

    //все элементы матрицы равны 0
    matrix m3 = createMatrixFromArray((int[]) {
                                              0, 0, 0,
                                              0, 0, 0,
                                              0, 0,  0,},
                                      3, 3);
    sortColsByMinElement(&m3);

    matrix exp_res3 = createMatrixFromArray((int[]) {
                                                    0, 0, 0,
                                                    0, 0, 0,
                                                    0, 0,  0,},
                                            3, 3);
    assert(areTwoMatricesEqual(&m3, &exp_res3));
    freeMemMatrix(&m3);
    freeMemMatrix(&exp_res3);
}


void test_mulMatrices(){
    //стандартный (простой) запуск функци
    matrix m1_1 = createMatrixFromArray((int[]) {
                                              1,  2,
                                              3, 4,},
                                      2, 2);
    matrix m1_2 = createMatrixFromArray((int[]) {
                                              5,  6,
                                              7, 8,},
                                      2, 2);
    matrix m1_3 = mulMatrices(m1_1, m1_2);
    matrix exp_res1 = createMatrixFromArray((int[]) {
                                                19,  22,
                                                43, 50,},
                                        2, 2);

    assert(areTwoMatricesEqual(&m1_3, &exp_res1));
    freeMemMatrix(&m1_1);
    freeMemMatrix(&m1_2);
    freeMemMatrix(&m1_3);
    freeMemMatrix(&exp_res1);

    //умножение на единичнкю матрицу
    matrix m3_1 = createMatrixFromArray((int[]) {
                                                5,  0, 0,
                                                0, 5, 0,
                                                0, 0, 5},
                                        3, 3);
    matrix m3_2 = createMatrixFromArray((int[]) {
                                                3,  0, 0,
                                                0, 3, 0,
                                                0, 0, 3},
                                        3, 3);
    matrix m3_3 = mulMatrices(m3_1, m3_2);
    matrix exp_res3 = createMatrixFromArray((int[]) {
                                                15,  0, 0,
                                                0, 15, 0,
                                                0, 0, 15},
                                        3, 3);
    assert(areTwoMatricesEqual(&m3_3, &exp_res3));
    freeMemMatrix(&m3_1);
    freeMemMatrix(&m3_2);
    freeMemMatrix(&m3_3);
    freeMemMatrix(&exp_res3);
}

void test_getSquareOfMatrixIfSymmetric(){
    //симметричная единичная матрица
    matrix m1 = createMatrixFromArray((int[]) {
                                                3,  0, 0,
                                                0, 3, 0,
                                                0, 0, 3},
                                        3, 3);
    getSquareOfMatrixIfSymmetric(&m1);
    matrix exp_res1 = createMatrixFromArray((int[]) {
                                                    9,  0, 0,
                                                    0, 9, 0,
                                                    0, 0, 9},
                                            3, 3);
    assert(areTwoMatricesEqual(&m1, &exp_res1));
    freeMemMatrix(&m1);
    freeMemMatrix(&exp_res1);

    //симметричная матрица
    matrix m2 = createMatrixFromArray((int[]) {
                                              19,  43,
                                              43, 50,},
                                      2, 2);
    getSquareOfMatrixIfSymmetric(&m2);
    matrix exp_res2 = createMatrixFromArray((int[]) {
                                                    2210,  2967,
                                                    2967, 4349,},
                                            2, 2);
    assert(areTwoMatricesEqual(&m2, &exp_res2));
    freeMemMatrix(&m2);
    freeMemMatrix(&exp_res2);

    //не симметричная матрица
    matrix m3 = createMatrixFromArray((int[]) {
                                              19,  89,
                                              43, 50,},
                                      2, 2);
    getSquareOfMatrixIfSymmetric(&m3);
    matrix exp_res3 = createMatrixFromArray((int[]) {
                                                    19,  89,
                                                    43, 50,},
                                            2, 2);
    assert(areTwoMatricesEqual(&m3, &exp_res3));
    freeMemMatrix(&m3);
    freeMemMatrix(&exp_res3);
}

void test_transposeIfMatrixHasNotEqualSumOfRows(){
    //суммы строк элементов не равны между собой
    matrix m1 = createMatrixFromArray((int[]) {
                                              15,  1, 2,
                                              0, 15, 0,
                                              3, 2, 3},
                                      3, 3);

    transposeIfMatrixHasNotEqualSumOfRows(m1);
    matrix exp_res1 = createMatrixFromArray((int[]) {
                                                   15,  0, 3,
                                                   1, 15, 2,
                                                   2, 0, 3},
                                           3, 3);
    assert(areTwoMatricesEqual(&m1, &exp_res1));
    freeMemMatrix(&m1);
    freeMemMatrix(&exp_res1);

    //среди сумм элементов строк есть равные
    matrix m2 = createMatrixFromArray((int[]) {
                                              15,  1, 2,
                                              3, 15, 0,
                                              3, 2, 3},
                                      3, 3);

    transposeIfMatrixHasNotEqualSumOfRows(m2);
    matrix exp_res2 = createMatrixFromArray((int[]) {
                                                    15,  1, 2,
                                                    3, 15, 0,
                                                    3, 2, 3},
                                            3, 3);
    assert(areTwoMatricesEqual(&m2, &exp_res2));
    freeMemMatrix(&m2);
    freeMemMatrix(&exp_res2);
}

void test_isMutuallyInverseMatrices(){
    //матрицы взаимно обратны
    matrix m1 = createMatrixFromArray((int[]) {
                                              1,  -2, 1,
                                              2, 1, -1,
                                              3, 2, -2},
                                      3, 3);

    matrix m2 = createMatrixFromArray((int[]) {
                                              0,  2, -1,
                                              -1, 5, -3,
                                              -1, 8, -5},
                                      3, 3);
    bool exp_res = true;
    assert(exp_res == isMutuallyInverseMatrices(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);

    //матрицы взаимно обратны
    matrix m1_1 = createMatrixFromArray((int[]) {
                                              1,  -2, 1,
                                              5, 1, -1,
                                              3, 2, -2},
                                      3, 3);

    matrix m2_1 = createMatrixFromArray((int[]) {
                                              0,  2, -1,
                                              -1, 5, -3,
                                              -1, 8, -5},
                                      3, 3);
    bool exp_res_1 = false;
    assert(exp_res_1 == isMutuallyInverseMatrices(m1_1, m2_1));

    freeMemMatrix(&m1_1);
    freeMemMatrix(&m2_1);
}

void test_findSumOfMaxesOfPseudoDiagonal(){
    matrix m = createMatrixFromArray((int[]) {
                                             3,  2, 5, 4,
                                             1, 3, 6, 3,
                                             3, 2, 1, 2},
                                     3, 4);

    assert(findSumOfMaxesOfPseudoDiagonal(m));
    freeMemMatrix(&m);
}

void test_getMinInAreal(){
    matrix m1 = createMatrixFromArray((int[]) {
                                             10,  7, 5, 6,
                                             3, 11, 8, 9,
                                             4, 1, 12, 2},
                                     3, 4);

    assert(findSumOfMaxesOfPseudoDiagonal(m1));
    freeMemMatrix(&m1);

    matrix m2 = createMatrixFromArray((int[]) {
                                              6,  8, 9, 2,
                                              7, 12, 3, 4,
                                              10, 11, 5, 1},
                                      3, 4);

    assert(findSumOfMaxesOfPseudoDiagonal(m2));
    freeMemMatrix(&m2);
}

void test_sortByDistances(){
    matrix m = createMatrixFromArray((int[]) {
                                             10, 11, 5, 1,
                                             7, 12, 3, 4,
                                             6,  8, 9, 2},
                                     3, 4);
    sortByDistances(m);

    matrix exp_res = createMatrixFromArray((int[]) {
                                                   6,  8, 9, 2,
                                                   7, 12, 3, 4,
                                                   10, 11, 5, 1},
                                           3, 4);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_countEqClassesByRowsSum(){
    matrix m = createMatrixFromArray((int[]) {
                                             7,1,
                                             2,7,
                                             5,4,
                                             4,3,
                                             1, 6,
                                             8, 0},
                                     6, 2);
    assert(countEqClassesByRowsSum(m) == 3);
    freeMemMatrix(&m);
}

void test_getNSpecialElement(){
    matrix m = createMatrixFromArray((int[]) {
                                             3,  5, 5, 4,
                                             2, 3, 6, 7,
                                             12, 2, 1, 2},
                                     3, 4);
    assert(getNSpecialElement(m) == 2);
    freeMemMatrix(&m);
}

void test_swapPenultimateRowWithMinimum(){
    matrix m = createMatrixFromArray((int[]) {
                                             1,  2, 3,
                                             4, 5, 6,
                                             7, 8, 1},
                                     3, 3);
    matrix exp_res = createMatrixFromArray((int[]) {
                                             1,  2, 3,
                                             1, 4, 7,
                                             7, 8, 1},
                                     3, 3);
    swapPenultimateRowWithMinimum(m);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_countNonDescendingRowsMatrices(){
    matrix *m = createArrayOfMatrixFromArray((int[]){
                                                     7, 1,
                                                     1,1,

                                                     1, 6,
                                                     2, 2,

                                                     5, 4,
                                                     2, 3,

                                                     1, 3,
                                                     7, 9},
                                             4, 2, 2);

    assert(countNonDescendingRowsMatrices(m, 4) == 2);
    freeMemMatrices(m, 4);
}

void test() {
    test_swapMinMaxRowsMatrix();
    test_sortRowsByMinElement();
    //test_sortColsByMinElement();
    test_mulMatrices();
    test_getSquareOfMatrixIfSymmetric();
    test_transposeIfMatrixHasNotEqualSumOfRows();
    test_isMutuallyInverseMatrices();
    test_findSumOfMaxesOfPseudoDiagonal();
    test_getMinInAreal();
    test_sortByDistances();
    test_countEqClassesByRowsSum();
    test_getNSpecialElement();
    test_swapPenultimateRowWithMinimum();
    test_countNonDescendingRowsMatrices();
}

int main() {
    test();

    return 0;
}