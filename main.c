#include "libs/matrix.h"

//1
void matrixToZero(matrix m){
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++)
            m.values[i][j] = 0;
    }
}

matrix addOnes(int n, int* query[], int operations){
    matrix m = getMemMatrix(n, n);
    matrixToZero(m);

    for (int i = 0; i < operations; i++){
        int begin_row = query[i][0];
        int begin_col = query[i][1];
        int end_row = query[i][2];
        int end_col = query[i][3];

        for (int j = begin_row; j <= end_row; j++){
            for (int k = begin_col; k <= end_col; k++)
                m.values[j][k] += 1;
        }
    }

    return m;
}

void test_task1(){
    int operation1[4] = {1,1,2,2};
    int operation2[4] = {0,0,1,1};
    int* query[2] = {operation1, operation2};
    matrix res = addOnes(3, query, 2);
    matrix exp = createMatrixFromArray((int[]) {
                                               1, 1, 0,
                                               1, 2, 1,
                                               0, 1, 1},
                                       3, 3);
    assert(areTwoMatricesEqual(&res, &exp));
    freeMemMatrix(&res);
    freeMemMatrix(&exp);
}

//2
int countNeighbours(matrix m, int index_row, int index_col){
    int begin_row = index_row - 1 >= 0 ? index_row - 1 : index_row;
    int begin_col = index_col - 1 >= 0 ? index_col - 1 : index_col;
    int end_row = index_row + 1 < m.nRows ? index_row + 1 : index_row;
    int end_col = index_col + 1 < m.nCols ? index_col + 1 : index_col;

    int counter = 0;

    for (int j = begin_row; j <= end_row; j++) {
        for (int k = begin_col; k <= end_col; k++)
            counter += m.values[j][k];
    }

    return counter - m.values[index_row][index_col];
}

void gameOfLife(matrix m){
    matrix temp = getMemMatrix(m.nRows, m.nCols);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            temp.values[i][j] = m.values[i][j];
    }

    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            int neighbours = countNeighbours(temp, i, j);
            if (neighbours < 2 || neighbours > 3)
                m.values[i][j] = 0;
            else if (neighbours == 3)
                m.values[i][j] = 1;
        }
    }

    freeMemMatrix(&temp);
}

void test_task2(){
    matrix m = createMatrixFromArray((int[]) {
                                             0, 1, 0,
                                             0, 0, 1,
                                             1, 1, 1,
                                             0, 0, 0},
                                     4, 3);
    matrix res = createMatrixFromArray((int[]) {
                                             0, 0, 0,
                                             1, 0, 1,
                                             0, 1, 1,
                                             0, 1, 0},
                                     4, 3);
    gameOfLife(m);
    assert(areTwoMatricesEqual(&m, &res));
    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

//3
int compare (const void * a, const void * b){
    return ( *(int*)a - *(int*)b );
}

int getMedian(matrix m, int index_row, int index_col){
    int array_window[8];

    array_window[0] = m.values[index_row - 1][index_col - 1];
    array_window[1] = m.values[index_row - 1][index_col];
    array_window[2] = m.values[index_row - 1][index_col + 1];
    array_window[3] = m.values[index_row][index_col - 1];
    array_window[4] = m.values[index_row][index_col + 1];
    array_window[5] = m.values[index_row + 1][index_col - 1];
    array_window[6] = m.values[index_row + 1][index_col];
    array_window[7] = m.values[index_row + 1][index_col + 1];

    qsort(array_window, 8, sizeof(int), compare);

    return (array_window[3] + array_window[4]) / 2;
}

void medianFilter(matrix m){
    for(int i = 1; i < m.nRows - 1; i++){
        for(int j = 1; j < m.nCols - 1; j++)
            m.values[i][j] = getMedian(m, i, j);
    }

}

void test_task3(){
    matrix m = createMatrixFromArray((int[]) {
                                             10, 20, 30,
                                             25, 35, 45,
                                             15, 25, 35},
                                     3, 3);
    matrix res = createMatrixFromArray((int[]) {
                                             10, 20, 30,
                                             25, 25, 45,
                                             15, 25, 35},
                                     3, 3);
    medianFilter(m);
    assert(areTwoMatricesEqual(&m, &res));
    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

void test(){
    test_task1();
    test_task2();
    test_task3();
}

int main() {
    test();

    return 0;
}