#include <stdio.h>
#include <stdlib.h>
#include "libs/matrix.h"
#include <assert.h>
#include <time.h>

//1

void transposeMatrixFile(const char* file_name){
    FILE *file = fopen(file_name, "r");

    int n;
    fscanf(file, "%d", &n);

    matrix matrix = getMemMatrix(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fscanf(file, "%d", &matrix.values[i][j]);
    }

    fclose(file);

    file = fopen(file_name, "w");

    transposeSquareMatrix(&matrix);

    fprintf(file, "%d\n", n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fprintf(file, "%d ", matrix.values[i][j]);

        fprintf(file, "\n");
    }

    fclose(file);
    freeMemMatrix(&matrix);
}

void test1_1(){
    char file_name[] = "aboba";
    int n = 1;
    int element = 10;

    FILE* file = fopen(file_name, "w");

    fprintf(file, "%d\n", n);
    fprintf(file, "%d\n", element);

    fclose(file);

    transposeMatrixFile(file_name);

    file = fopen(file_name, "r");

    int n_res, element_res;
    fscanf(file, "%d\n", &n_res);
    fscanf(file, "%d\n", &element_res);

    assert(element == element_res);

    fclose(file);
}

void test1_2(){
    char file_name[] = "aboba";
    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1}, 3, 3);

    matrix m_res = createMatrixFromArray((int[]) {1, 0, 0,
                                                  0, 1, 0,
                                                  0, 0, 1}, 3, 3);

    FILE* file = fopen(file_name, "w");

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++)
            fprintf(file, "%d ", m.values[i][j]);

        fprintf(file, "\n");
    }

    fclose(file);

    transposeMatrixFile(file_name);

    int n_res;
    matrix m_res_test = getMemMatrix(n, n);

    file = fopen(file_name, "r");

    fscanf(file, "%d\n", &n_res);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &m_res_test.values[i][j]);

    fclose(file);

    assert(areTwoMatricesEqual(&m_res, &m_res_test));

    freeMemMatrix(&m);
    freeMemMatrix(&m_res_test);
    freeMemMatrix(&m_res);
}

void test1_3(){
    char file_name[] = "aboba";
    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    matrix m_res = createMatrixFromArray((int[]) {1, 4, 7,
                                                  2, 5, 8,
                                                  3, 6, 9}, 3, 3);

    FILE* file = fopen(file_name, "w");

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++)
            fprintf(file, "%d ", m.values[i][j]);

        fprintf(file, "\n");
    }

    fclose(file);

    transposeMatrixFile(file_name);

    int n_res;
    matrix m_res_test = getMemMatrix(n, n);

    file = fopen(file_name, "r");

    fscanf(file, "%d\n", &n_res);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &m_res_test.values[i][j]);

    fclose(file);

    assert(areTwoMatricesEqual(&m_res, &m_res_test));

    freeMemMatrix(&m);
    freeMemMatrix(&m_res_test);
    freeMemMatrix(&m_res);
}


void test1(){
    test1_1();
    test1_2();
    test1_3();
}

void test(){
    test1();
}

int main() {
    test();
    return 0;
}