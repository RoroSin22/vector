#include <stdio.h>
#include <stdbool.h>
#include "libs/matrix.h"

int getSum(int *a, int n){
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];

    return sum;
}

int getDifference(int *a, int n){
    int difference = 0;
    for (int i = 0; i < n; i++)
        difference -= a[i];

    return difference;
}

int main() {
    matrix a = getMemMatrix(3, 2);
    inputMatrix(&a);
    transposeMatrix(&a);
    outputMatrix(a);

    return 0;
}