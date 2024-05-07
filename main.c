#include <stdio.h>
#include <stdbool.h>
#include "libs/string_.h"
#include <assert.h>

void test_removeExtraSpaces() {
    char str[] = "";
    char exp[] = "";
    removeExtraSpaces(str);
    ASSERT_STRING(exp, str);
    char str1[] = "I'm   so";
    char exp1[] = "I'm so";
    removeExtraSpaces(str1);
    ASSERT_STRING(exp1, str1);
    char str2[] = "I'm  so   tired  ";
    char exp2[] = "I'm so tired ";
    removeExtraSpaces(str2);
    ASSERT_STRING(exp2, str2);
}



void test(){
    test_removeExtraSpaces();
}

int main() {
    test();

    return 0;
}