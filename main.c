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

void test() {
    test_swapMinMaxRowsMatrix();
    test_sortRowsByMinElement();
    test_sortColsByMinElement();
}
int main() {
    test();

    return 0;
}