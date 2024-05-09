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

void test_isPalindrome(){
    char *str = "racecar";
    WordDescriptor word;
    getWord(str, &word);
    assert(isPalindrome(word) == 1);
    char *str1 = "racecars";
    WordDescriptor word1;
    getWord(str1, &word1);
    assert(!isPalindrome(word1));
}

void test_countPalindromes(){
    char s[] = "";
    assert(countPalindromes(s) == 0);
    char s1[] = "aaa bb ab";
    assert(countPalindromes(s1) == 2);
}

void test_combinedString(){
    char s1[] = "";
    char s2[] = "";
    char res[0];
    char exp[] = "";
    combinedSting(s1,s2,res);
    ASSERT_STRING(res, exp);
    char s1_1[] = "this work like";
    char s2_1[] = "laboratory feels eternity";
    char res_1[strlen_(s1_1) + strlen_(s2_1)];
    char exp_1[] = "this laboratory work feels like eternity";
    combinedSting(s1_1,s2_1,res_1);
    ASSERT_STRING(res_1, exp_1);
    char s1_2[] = "just";
    char s2_2[] = "another test";
    char res_2[strlen_(s1_2) + strlen_(s2_2)];
    char exp_2[] = "just another test";
    combinedSting(s1_2,s2_2,res_2);
    ASSERT_STRING(res_2, exp_2);
}

void testAll_getWordBeforeFirstWordWithA() {
    WordDescriptor word;
    char s1[] = "";
    assert(
            getWordBeforeFirstWordWithA(s1, &word)
            == EMPTY_STRING
    );
    char s2[] = "ABC";
    assert(
            getWordBeforeFirstWordWithA(s2, &word)
            == FIRST_WORD_WITH_A
    );
    char s3[] = "BC A";
    assert(
            getWordBeforeFirstWordWithA(s3, &word)
            == WORD_FOUND
    );
    char got[MAX_WORD_SIZE];
    copy(word.begin, word.end, got);
    got[word.end - word.begin] = '\0';
    ASSERT_STRING("BC", got);
    char s4[] = "B Q WE YR OW IUWR";
    assert(getWordBeforeFirstWordWithA(s4, &word) == NOT_FOUND_A_WORD_WITH_A);
}

void test(){
    test_removeExtraSpaces();
    test_digitsToEndWordInSentence();
    test_numbersToSpaces();
    test_replace();
    test_areByAlphabet();
    test_isPalindrome();
    test_countPalindromes();
    test_combinedString();
    testAll_getWordBeforeFirstWordWithA();
}

int main() {
    testAll_getWordBeforeFirstWordWithA();
    return 0;
}