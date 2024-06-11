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

int main() {
    testAreLinesEqual();
    return 0;
}