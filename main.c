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

void test_numbersToSpaces(){
    char s[] = "";
    char s_changed[1];
    char exp[] = "";
    numbersToSpaces(s, s_changed);
    ASSERT_STRING(exp, s_changed);
    char s1[] = "a1b2c";
    char s1_changed[7];
    char exp1[] = "a b  c";
    numbersToSpaces(s1, s1_changed);
    ASSERT_STRING(exp1, s1_changed);
    char s2[] = "4";
    char s2_changed[5];
    char exp2[] = "    ";
    numbersToSpaces(s2, s2_changed);
    ASSERT_STRING(exp2, s2_changed);
    char s3[] = "2test3";
    char s3_changed[10];
    char exp3[] = "  test   ";
    numbersToSpaces(s3, s3_changed);
    ASSERT_STRING(exp3, s3_changed);
}

void test_replace(){
    char str[] = "";
    char w1[] = "";
    char w2[] = "";
    replace(str, w1, w2);
    char exp[] = "";
    ASSERT_STRING(exp, str);
    char str1[] = "I'm fine";
    char w1_1[] = "fine";
    char w2_1[] = "tired";
    replace(str1, w1_1, w2_1);
    char exp1[] = "I'm tired";
    ASSERT_STRING(exp1, str1);
    char str2[] = "  That's a simple word, really simple   ";
    char w1_2[] = "simple";
    char w2_2[] = "hard";
    replace(str2, w1_2, w2_2);
    char exp2[] = "  That's a hard word, really hard   ";
    ASSERT_STRING(exp2, str2);
}

void test_areByAlphabet(){
    char str[] = "aa ab ac";
    assert(areByAlphabet(str) == 1);
    char str1[] = "";
    assert(areByAlphabet(str1) == 1);
    char str2[] = "That's not by alphabet";
    assert(areByAlphabet(str2) == 0);
}

void test(){
    test_removeExtraSpaces();
    test_digitsToEndWordInSentence();
    test_numbersToSpaces();
    test_replace();
    test_areByAlphabet();
}

int main() {
    test();
    return 0;
}