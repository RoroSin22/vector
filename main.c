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

    assert(exp_res1 == &s1[3]);
    assert(exp_res2 == &s2[0]);
    assert(exp_res3 == &s3[3]);
    assert(exp_res4 == &s4[0]);
}

void test_findSpace(){
    char *s1 = "   Hi";
    char *s2 = "hii";
    char s3[10] = "   ";
    char s4[10] = "hi ";

    char* exp_res1 = findSpace(s1);
    char* exp_res2 = findSpace(s2);
    char* exp_res3 = findSpace(s3);
    char* exp_res4 = findSpace(s4);

    assert(exp_res1 == &s1[0]);
    assert(exp_res2 == &s2[3]);
    assert(exp_res3 == &s3[0]);
    assert(exp_res4 == &s4[2]);
}

void test_findNonSpaceReverse(){
    char *s1 = "   Hi";
    char *s2 = "i ";
    char s3[10] = "   ";
    char s4[10] = "h i ";

    char* exp_res1 = findNonSpaceReverse(&s1[4], &s1[-1]);
    char* exp_res2 = findNonSpaceReverse(&s2[1], &s2[-1]);
    char* exp_res3 = findNonSpaceReverse(&s3[2], &s3[-1]);
    char* exp_res4 = findNonSpaceReverse(&s4[3], &s4[-1]);

    assert(exp_res1 == &s1[4]);
    assert(exp_res2 == &s2[0]);
    assert(exp_res3 == &s3[-1]);
    assert(exp_res4 == &s4[2]);
}

void test_findSpaceReverse(){
    char *s1 = "   Hi";
    char *s2 = "hii";
    char s3[10] = "   ";
    char s4[10] = "h i ";

    char* exp_res1 = findSpaceReverse(&s1[4], &s1[-1]);
    char* exp_res2 = findSpaceReverse(&s2[2], &s2[-1]);
    char* exp_res3 = findSpaceReverse(&s3[2], &s3[-1]);
    char* exp_res4 = findSpaceReverse(&s4[3], &s4[-1]);

    assert(exp_res1 == &s1[2]);
    assert(exp_res2 == &s2[-1]);
    assert(exp_res3 == &s3[2]);
    assert(exp_res4 == &s4[3]);
}

void test_strcmp_(){
    char *s1_1 = "aaa";
    char *s2_1 = "aaa";
    char *s1_2 = "bba";
    char *s2_2 = "bbb";
    char *s1_3 = "aab";
    char *s2_3 = "aaa";

    assert(strcmp_(s1_1, s2_1) == 0);
    assert(strcmp_(s1_2, s2_2) == -1);
    assert(strcmp_(s1_3, s2_3) == 1);
}

void test(){
    test_findNonSpace();
    test_findSpace();
    test_findNonSpaceReverse();
    test_findSpaceReverse();
    test_strcmp_();
}

int main() {
    test();
    return 0;
}