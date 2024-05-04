#include <stdio.h>
#include <stdbool.h>
#include "libs/string_.h"
#include <assert.h>

void test_findNonSpace(){
    char *s1 = "   Hi";
    char *s2 = "i ";
    char s3[10] = "   ";
    char s4[10] = "h i ";

    char* exp_res1 = findNonSpace(s1);
    char* exp_res2 = findNonSpace(s2);
    char* exp_res3 = findNonSpace(s3);
    char* exp_res4 = findNonSpace(s4);

    assert(exp_res1[0] == s1[3]);
    assert(exp_res2[0] == s2[0]);
    assert(exp_res3[0] == '\0');
    assert(exp_res4[0] == s4[0]);
}

int main() {
    test_findNonSpace();
    return 0;
}