#include <stdio.h>
#include <stdlib.h>
#include "libs/matrix.h"
#include <assert.h>
#include <time.h>
#include "libs/vectorVoid.h"
#include "libs/string_.h"
#define NUMBER_CONST 48

bool fequal(float a, float b){
    return fabs(a-b) < DBL_EPSILON;
}

//1

void transposeMatrixFile(const char* file_name){
    FILE *file = fopen(file_name, "r");

    int n;
    fscanf(file, "%d", &n);

    matrix matrix = getMemMatrix(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fscanf(file, "%d", &matrix.values[i][j]);
    }

    fclose(file);

    file = fopen(file_name, "w");

    transposeSquareMatrix(&matrix);

    fprintf(file, "%d\n", n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fprintf(file, "%d ", matrix.values[i][j]);

        fprintf(file, "\n");
    }

    fclose(file);
    freeMemMatrix(&matrix);
}

void test1_1(){
    char file_name[] = "aboba";
    int n = 1;
    int element = 10;

    FILE* file = fopen(file_name, "w");

    fprintf(file, "%d\n", n);
    fprintf(file, "%d\n", element);

    fclose(file);

    transposeMatrixFile(file_name);

    file = fopen(file_name, "r");

    int n_res, element_res;
    fscanf(file, "%d\n", &n_res);
    fscanf(file, "%d\n", &element_res);

    assert(element == element_res);

    fclose(file);
}

void test1_2(){
    char file_name[] = "aboba";
    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1}, 3, 3);

    matrix m_res = createMatrixFromArray((int[]) {1, 0, 0,
                                                  0, 1, 0,
                                                  0, 0, 1}, 3, 3);

    FILE* file = fopen(file_name, "w");

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++)
            fprintf(file, "%d ", m.values[i][j]);

        fprintf(file, "\n");
    }

    fclose(file);

    transposeMatrixFile(file_name);

    int n_res;
    matrix m_res_test = getMemMatrix(n, n);

    file = fopen(file_name, "r");

    fscanf(file, "%d\n", &n_res);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &m_res_test.values[i][j]);

    fclose(file);

    assert(areTwoMatricesEqual(&m_res, &m_res_test));

    freeMemMatrix(&m);
    freeMemMatrix(&m_res_test);
    freeMemMatrix(&m_res);
}

void test1_3(){
    char file_name[] = "aboba";
    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    matrix m_res = createMatrixFromArray((int[]) {1, 4, 7,
                                                  2, 5, 8,
                                                  3, 6, 9}, 3, 3);

    FILE* file = fopen(file_name, "w");

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++)
            fprintf(file, "%d ", m.values[i][j]);

        fprintf(file, "\n");
    }

    fclose(file);

    transposeMatrixFile(file_name);

    int n_res;
    matrix m_res_test = getMemMatrix(n, n);

    file = fopen(file_name, "r");

    fscanf(file, "%d\n", &n_res);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &m_res_test.values[i][j]);

    fclose(file);

    assert(areTwoMatricesEqual(&m_res, &m_res_test));

    freeMemMatrix(&m);
    freeMemMatrix(&m_res_test);
    freeMemMatrix(&m_res);
}

void test1(){
    test1_1();
    test1_2();
    test1_3();
}

//2
void convert_float(const char* file_name) {
    FILE* file = fopen(file_name, "r");

    vectorVoid v = createVectorV(0, sizeof(float));

    while (!feof(file)) {
        float x;
        fscanf(file, "%f", &x);
        pushBackV(&v, &x);
    }

    fclose(file);

    file = fopen(file_name, "w");

    for (size_t i = 0; i < v.size; i++) {
        float x;
        getVectorValueV(&v, i, &x);
        fprintf(file, "%.2f ", x);
    }

    deleteVectorV(&v);
    fclose(file);
}

void test_convert_float(){
    const char file_name[] = "aboba";

    vectorVoid v = createVectorV(3, sizeof(float));
    float number1 = 7.143423;
    pushBackV(&v, &number1);
    float number2 = 2.241518;
    pushBackV(&v, &number2);
    float number3 = 9.353738;
    pushBackV(&v, &number3);

    FILE* file = fopen(file_name, "w");

    for (size_t i = 0; i < v.size; i++) {
        float x;
        getVectorValueV(&v, i, &x);
        fprintf(file, "%.2f ", x);
    }

    fclose(file);

    convert_float(file_name);

    vectorVoid v_exp = createVectorV(3, sizeof(float));
    float number1_exp = 7.143423;
    pushBackV(&v_exp, &number1_exp);
    float number2_exp = 2.241518;
    pushBackV(&v_exp, &number2_exp);
    float number3_exp = 9.353738;
    pushBackV(&v_exp, &number3_exp);

    file = fopen(file_name, "r");

    for (int i = 0; i < 3; i++) {
        float y;
        float y_exp;
        fscanf(file, "%f\n", &y);
        getVectorValueV(&v_exp, sizeof(float), &y_exp);
        assert(fequal(y, y_exp) == 0);
    }

    fclose(file);

    deleteVectorV(&v);
    deleteVectorV(&v_exp);
}

//3
int doMath(int number1, char operation, int number2){
    switch (operation){
        case '+':
            return number1 + number2;
        case '-':
            return number1 - number2;
        case '*':
            return number1 * number2;
        case '/':
            if (number2 == 0) {
                fprintf(stderr, "dividing on zero");
                exit(1);
            }
            return number1 / number2;
    }

    fprintf(stderr, "there is no operation");
}

void solveMathProblem(const char* file_name){
    FILE* file = fopen(file_name, "r");

    char symbols_in_file[6];
    int result;
    int i = 0;
    for (; i <= 5 && !feof(file); i++)
        fscanf(file, "%c", &symbols_in_file[i]);

    fclose(file);

    symbols_in_file[i - 1] = '\0';

    int number1 = symbols_in_file[0] - NUMBER_CONST;
    int number2 = symbols_in_file[2] - NUMBER_CONST;

    if (symbols_in_file[3] == '\0'){
        result = doMath(number1, symbols_in_file[1], number2);
    }else{
        int number3 = symbols_in_file[4] - NUMBER_CONST;

        if ((symbols_in_file[1] != '*' && symbols_in_file[1] != '/') && (symbols_in_file[3] == '*' || symbols_in_file[3] == '/')){
            result = doMath(number2, symbols_in_file[3], number3);
            result = doMath(number1, symbols_in_file[1], result);
        }else{
            result = doMath(number1, symbols_in_file[1], number2);
            result = doMath(result, symbols_in_file[3], number3);
        }
    }

    file = fopen(file_name, "a+");

    fprintf(file, "%c", '=');
    if (result > 9){
        fprintf(file, "%c", result / 10 + NUMBER_CONST);
        fprintf(file, "%c", result % 10 + NUMBER_CONST);
    } else if (result < 0){
        if(result < -9) {
            fprintf(file, "%c", '-');
            fprintf(file, "%c", -1 * result / 10 + NUMBER_CONST);
            fprintf(file, "%c", -1 * result % 10 + NUMBER_CONST);
        }else{
            fprintf(file, "%c", '-');
            fprintf(file, "%c", -1 * result + NUMBER_CONST);
        }
    }else
        fprintf(file, "%c", result + NUMBER_CONST);

    fclose(file);
}

void test3_1(){
    FILE* file = fopen("aboba", "w");
    fprintf(file, "5+4");
    fclose(file);
    solveMathProblem("aboba");

    file = fopen("aboba", "r");
    char result[10];
    fscanf(file, "%s\n", &result);
    fclose(file);

    char exp_result[] = "5+4=9";
    assert(strcmp(result, exp_result) == 0);
}

void test3_2(){
    FILE* file = fopen("aboba", "w");
    fprintf(file, "9-4*2");
    fclose(file);
    solveMathProblem("aboba");

    file = fopen("aboba", "r");
    char result[10];
    fscanf(file, "%s\n", &result);
    fclose(file);

    char exp_result[] = "9-4*2=1";
    assert(strcmp(result, exp_result) == 0);
}

void test3_3(){
    FILE* file = fopen("aboba", "w");
    fprintf(file, "8*9");
    fclose(file);
    solveMathProblem("aboba");

    file = fopen("aboba", "r");
    char result[10];
    fscanf(file, "%s\n", &result);
    fclose(file);

    char exp_result[] = "8*9=72";
    assert(strcmp(result, exp_result) == 0);
}

void test3_4(){
    FILE* file = fopen("aboba", "w");
    fprintf(file, "8/2-5");
    fclose(file);
    solveMathProblem("aboba");

    file = fopen("aboba", "r");
    char result[10];
    fscanf(file, "%s\n", &result);
    fclose(file);

    char exp_result[] = "8/2-5=-1";
    assert(strcmp(result, exp_result) == 0);
}

void test3_5(){
    FILE* file = fopen("aboba", "w");
    fprintf(file, "6*4/8");
    fclose(file);
    solveMathProblem("aboba");

    file = fopen("aboba", "r");
    char result[10];
    fscanf(file, "%s\n", &result);
    fclose(file);

    char exp_result[] = "6*4/8=3";
    assert(strcmp(result, exp_result) == 0);
}

void test3(){
    test3_1();
    test3_2();
    test3_3();
    test3_4();
    test3_5();
}

//4
void deleteNonSequenceWords(char* str, const char* sequence){
    copy(str, getEndOfString(str), _stringBuffer);
    getBagOfWords(&_bag, str);
    char* current = str;
    char word[MAX_WORD_SIZE];

    for (int i = 0; i < _bag.size ; i++){
        wordDescriptorToString(_bag.words[i], &word);

        if (strstr(word, sequence) != NULL){
            copy(_bag.words[i].begin, _bag.words[i].end + 1, current);
            current += _bag.words[i].end - _bag.words[i].begin + 1;
        }

    }
    *current = '\0';
    current++;
    *current = '\n';
}

void deleteNonSequenceWordsFile(const char* file_name, const char* sequence){
    FILE* file = fopen(file_name, "r");
    char str[MAX_STRING_SIZE];
    fscanf(file, "%[^\n]", &str);
    fclose(file);

    deleteNonSequenceWords(str, sequence);

    file = fopen(file_name, "w");
    fprintf(file, "%s\n", str);
    fclose(file);
}

void test4_1() {
    const char file_name[] = "aboba";
    char str[] = "Good Lord";
    FILE* file = fopen(file_name, "w");
    fprintf(file, &str);
    fclose(file);
    deleteNonSequenceWordsFile(file_name, "Lord");
    file = fopen(file_name, "r");
    char res[MAX_STRING_SIZE];
    fscanf(file, "%[^\n]", res);
    fclose(file);
    char exp_res[] = "Good";
    assert(strcmp(res, exp_res));
}

void test4_2() {
    const char file_name[] = "aboba";
    char str[] = "there are sevarale words are";
    FILE* file = fopen(file_name, "w");
    fprintf(file, str);
    fclose(file);
    deleteNonSequenceWordsFile(file_name, "are");
    file = fopen(file_name, "r");
    char res[MAX_STRING_SIZE];
    fscanf(file, "%[^\n]", res);
    fclose(file);
    char exp_res[] = "are sevarale are";
    assert(strcmp(res, exp_res));
}

void test4_3() {
    const char file_name[] = "aboba";
    char str[] = "there is no parts of sequence";
    FILE* file = fopen(file_name, "w");
    fprintf(file, str);
    fclose(file);
    deleteNonSequenceWordsFile(file_name, "word");
    file = fopen(file_name, "r");
    char res[MAX_STRING_SIZE];
    fscanf(file, "%[^\n]", res);
    fclose(file);
    char exp_res[] = "there is no parts of sequence";
    assert(strcmp(res, exp_res));
}

void test4(){
    test4_1();
    test4_2();
    test4_3();
}

//test
void test(){
    test1();
    test_convert_float();
    test3();
    test4();
}

int main() {
    test();
    return 0;
}