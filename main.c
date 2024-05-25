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
            for (int k = begin_col; k <= end_col; k++) {
                m.values[j][k] += 1;
            }
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

void test(){
    test_task1();
}

int main() {
    test();
    return 0;
}