#include <stdio.h>
#include <stdbool.h>
#include "libs/string_.h"
#include <assert.h>

void test_removeExtraSpaces(){
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

void test_digitsToEndWordInSentence(){
    char str[] = "";
    char exp[] = "";
    digitsToEndWordInSentence(str);
    ASSERT_STRING(exp, str);
    char str1[] = "11he he11 1he1 h1e1";
    char exp1[] = "he11 he11 he11 he11";
    digitsToEndWordInSentence(str1);
    ASSERT_STRING(exp1, str1);
}

void test(){
    test_removeExtraSpaces();
    test_digitsToEndWordInSentence();
}

int main() {
    test();
    return 0;
}