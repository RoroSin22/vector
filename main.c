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

void test() {
    test_swapMinMaxRowsMatrix();

}

int main() {
    test();

    return 0;
}