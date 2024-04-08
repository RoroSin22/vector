#include <stdio.h>
#include <stdbool.h>
#include "libs/matrix.h"

int main() {
    matrix a = getMemMatrix(3, 3);
    inputMatrix(&a);
    swapRows(a, 0, 2);
    outputMatrix(a);

    return 0;
}