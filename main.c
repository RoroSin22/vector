#include "libs/matrix.h"

bool areLinesEqual(int* line_one, int* line_two, int n){
    if (n <= 0)
        return 0;

    return memcmp(line_one, line_two, sizeof(int) * n) == 0;
}

void testAreLinesEqual_1(){
    int n = 0;
    int line_one1[n] = {};
    int line_one2[n] = {};
    assert(areLinesEqual(line_one1, line_one2, n) == 0);
}

void testAreLinesEqual_2(){
    int n = 3;
    int line_one1[3] = {1, 2, 3};
    int line_one2[3] = {1, 2, 3};
    assert(areLinesEqual(line_one1, line_one2, n) == 1);
}

void testAreLinesEqual_3(){
    int n = 4;
    int line_one1[4] = {1, 2, 3, 6};
    int line_one2[4] = {1, 2, 5, 3};
    assert(areLinesEqual(line_one1, line_one2, n) == 0);
}

void testAreLinesEqual(){
    testAreLinesEqual_1();
    testAreLinesEqual_2();
    testAreLinesEqual_3();
}

bool matrixCanBeEqual(matrix m1, matrix m2){
    int matrix_size = m1.nRows;
    bool exeption_array[matrix_size];
    for (int i = 0; i < matrix_size; i++)
        exeption_array[i] = 1;

    for(int i = 0; i < matrix_size; i++){
        for(int j = 0; j < matrix_size; j++){
            if (exeption_array[j] == 0)
                continue;
            if (areLinesEqual(m1.values[i], m2.values[j], matrix_size)){
                exeption_array[j] = 0;
                break;
            }
        }
    }

    for (int i = 0; i < matrix_size; i++){
        if (exeption_array[i] == 1)
            return 0;
    }

    return 1;
}

void testMatrixCanBeEqual1(){
    matrix m1 = createMatrixFromArray((int[]){1, 2, 3,
                                              7, 8, 9,
                                              4, 5, 6}, 3, 3);
    matrix m2 = createMatrixFromArray((int[]){1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    assert(matrixCanBeEqual(m1, m2) == 1);
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void testMatrixCanBeEqual2(){
    matrix m1 = createMatrixFromArray((int[]){}, 0, 0);
    matrix m2 = createMatrixFromArray((int[]){}, 0, 0);

    assert(matrixCanBeEqual(m1, m2) == 1);
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void testMatrixCanBeEqual3(){
    matrix m1 = createMatrixFromArray((int[]){1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);
    matrix m2 = createMatrixFromArray((int[]){1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    assert(matrixCanBeEqual(m1, m2) == 1);
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void testMatrixCanBeEqual4(){
    matrix m1 = createMatrixFromArray((int[]){1, 2, 3,
                                              7, 8, 9,
                                              4, 5, 6}, 3, 3);
    matrix m2 = createMatrixFromArray((int[]){1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    assert(matrixCanBeEqual(m1, m2) == 1);
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void testMatrixCanBeEqual5(){
    matrix m1 = createMatrixFromArray((int[]){1, 2, 3,
                                              7, 8, 9,
                                              4, 5, 6}, 3, 3);
    matrix m2 = createMatrixFromArray((int[]){1, 2, 3,
                                              4, 3, 6,
                                              7, 2, 9}, 3, 3);

    assert(matrixCanBeEqual(m1, m2) == 0);
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void testMatrixCanBeEqual(){
    testMatrixCanBeEqual1();
    testMatrixCanBeEqual2();
    testMatrixCanBeEqual3();
    testMatrixCanBeEqual4();
    testMatrixCanBeEqual5();
}


int main() {
    testMatrixCanBeEqual();

    return 0;
}