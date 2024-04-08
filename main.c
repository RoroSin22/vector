#include <stdio.h>
#include <stdbool.h>
#include "libs/matrix.h"

int main() {
    matrix a = getMemMatrix(3, 3);
    inputMatrix(&a);
    outputMatrix(a);

    return 0;
}