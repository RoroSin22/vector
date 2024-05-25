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
}

void test(){
    test_task1();
    test_task2();
}

int main() {
    test();
    return 0;
}