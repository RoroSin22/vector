#include <stdio.h>
#include <stdlib.h>
#include "libs/matrix.h"
#include <assert.h>
#include <time.h>
#include <math.h>
#include "libs/vectorVoid.h"
#include "libs/vector.h"
#include "libs/string_.h"
#define NUMBER_CONST 48
#define MAX_LINES 20

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
    char exp_res[] = "Lord";
    assert(strcmp(res, exp_res) == 0);
}

void test4_2() {
    const char file_name[] = "aboba";
    char str[] = "there are sevarele words are";
    FILE* file = fopen(file_name, "w");
    fprintf(file, str);
    fclose(file);
    deleteNonSequenceWordsFile(file_name, "are");
    file = fopen(file_name, "r");
    char res[MAX_STRING_SIZE];
    fscanf(file, "%[^\n]", res);
    fclose(file);
    char exp_res[] = "are sevarele are";
    assert(strcmp(res, exp_res) == 0);
}

void test4(){
    test4_1();
    test4_2();
}

//5
WordDescriptor longestWord(char* str){
    getBagOfWords(&_bag, str);
    WordDescriptor longest_word;
    passWordPosition(&longest_word, &_bag.words[0]);
    int max_len = longest_word.end - longest_word.begin;

    for (int i = 1; i < _bag.size; i++){
        int word_len = _bag.words[i].end - _bag.words[i].begin;
        if (max_len < word_len){
            passWordPosition(&longest_word, &_bag.words[i]);
            max_len = word_len;
        }
    }

    return longest_word;
}

size_t getLinesAmountFile(const char* file_name){
    FILE* file = fopen(file_name, "r");

    size_t counter = 0;
    char str[MAX_STRING_SIZE];
    while (fgets(str, MAX_STRING_SIZE, file) != NULL)
        counter++;


    fclose(file);
    return counter;
}

void onlyLongestWordsFile(const char* file_name){
    FILE* file = fopen(file_name, "r");
    size_t lines_amount = getLinesAmountFile(file_name);

    char* words = (char *) malloc(sizeof(char) * MAX_WORD_SIZE * lines_amount);
    char string[MAX_STRING_SIZE];
    for (int i = 0; i < lines_amount; i++){
        fgets(string, MAX_STRING_SIZE, file);
        WordDescriptor longest_word = longestWord(string);
        char word[MAX_WORD_SIZE];
        wordDescriptorToString(longest_word, word);
        memcpy(&words[i * MAX_WORD_SIZE + 1], word, sizeof(char) * (longest_word.end - longest_word.begin + 1));
    }

    fclose(file);

    file = fopen(file_name,"w");

    for (int i = 0; i < lines_amount; i++)
        fprintf(file, "%s\n", &words[i * MAX_WORD_SIZE + 1]);

    fclose(file);
}

void test5_1(){
    char* str1 = "test this function\n";
    char* exp1 = "function";


    FILE* f = fopen("aboba", "w");
    fputs(str1, f);
    fclose(f);

    onlyLongestWordsFile("aboba");

    f = fopen("aboba", "r");
    char str[MAX_STRING_SIZE];
    fscanf(f, "%s\n", str);
    fclose(f);

    assert(strcmp(str, exp1) == 0);
}

void test5_2(){
    char* str1 = "there are some random sentences\n";
    char* str2 = "they do not have\n";
    char* str3 = "any sense it is just test\n";

    char* exp1 = "sentences";
    char* exp2 = "they";
    char* exp3 = "sense";

    FILE* f = fopen("aboba", "w");
    fputs(str1, f);
    fputs(str2, f);
    fputs(str3, f);
    fclose(f);

    onlyLongestWordsFile("aboba");

    f = fopen("aboba", "r");
    char str[MAX_STRING_SIZE];
    fscanf(f, "%s\n", str);
    assert(strcmp(str, exp1) == 0);
    fscanf(f, "%s\n", str);
    assert(strcmp(str, exp2) == 0);
    fscanf(f, "%s\n", str);
    assert(strcmp(str, exp3) == 0);

    fclose(f);
}

void test5(){
    test5_1();
    test5_2();
}

//6
/*
typedef struct {
    int power;
    int coefficient;
}polynomial;

polynomial* getMemArrayPolynomial(int nPolynomial){
    polynomial *ps = (polynomial *) malloc(sizeof(polynomial) * nPolynomial);
    return ps;
}

bool isRoot(polynomial* ps, int x){
    int res = 0;
    int position = 0;
    while (ps[position].power != 0){
        res += ps[position].coefficient * (int) round(pow(x, ps[position].power));
        position++;
    }
    res += ps[position].coefficient;
    return res == 0;
}

void task6(const char* file_name, int x){
    FILE* file = fopen(file_name, "rb");
    FILE* temporary = fopen("temp", "w+b");

    while (!feof(file)) {
        int element_amount;
        fread(&element_amount, sizeof(int), 1, file);
        polynomial* ps = getMemArrayPolynomial(element_amount);

        fread(ps, sizeof(polynomial), element_amount, file);

        if (isRoot(ps, x))
            fwrite(ps, sizeof(polynomial), element_amount, temporary);
    }

    fclose(file);
    fclose(temporary);

    file = fopen(file_name, "wb");
    temporary = fopen("temp", "rb");
    int c;
    while ((c = fgetc(temporary)) != EOF)
        fputc(c, file);

    fclose(file);
    fclose(temporary);
} */

//7
void negativeToEndFile(const char* file_name) {
    FILE* file = fopen(file_name, "rb");
    vector positive_num = createVector(3);
    vector negative_num = createVector(3);


    int corrective_num;
    while (fread(&corrective_num, sizeof(int), 1, file) == 1) {
        if (corrective_num >= 0)
            pushBack(&positive_num, corrective_num);
        else
            pushBack(&negative_num, corrective_num);
    }

    fclose(file);
    file = fopen(file_name, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }
    for (int i = 0; i < positive_num.size; i++)
        fwrite(positive_num.data + i, sizeof(int), 1, file);
    for (int i = 0; i < negative_num.size; i++)
        fwrite(negative_num.data + i, sizeof(int), 1, file);
    deleteVector(&positive_num);
    deleteVector(&negative_num);
    fclose(file);
}

void test7_1(){
    const char filename[] = "aboba";
    int num[4] = {2, 4, -1, -8};
    FILE* file = fopen(filename, "wb");
    for (int i = 0; i < 4; i++)
        fwrite(&num[i], sizeof(int), 1, file);

    fclose(file);
    negativeToEndFile(filename);
    file = fopen(filename, "rb");
    int exp[4];
    for (int i = 0; i < 4; i++)
        fread(&exp[i], sizeof(int), 1, file);

    fclose(file);
    for (int i = 0; i < 4; i++)
        assert(num[i] == exp[i]);
}

void test7_2(){
    const char filename[] = "aboba";
    int num[6] = {2, -4, 1, -8, 7, 9};
    FILE* file = fopen(filename, "wb");
    for (int i = 0; i < 6; i++)
        fwrite(&num[i], sizeof(int), 1, file);

    fclose(file);
    negativeToEndFile(filename);
    file = fopen(filename, "rb");
    int res[6];
    int exp[6] = {2, 1, 7, 9, -4, -8};
    for (int i = 0; i < 6; i++) {
        fread(&res[i], sizeof(int), 1, file);
        assert(res[i] == exp[i]);
    }

    fclose(file);
}

void test7_3(){
    const char filename[] = "aboba";
    int num[6] = {-2, -4, -1, 8, 7, 9};
    FILE* file = fopen(filename, "wb");
    for (int i = 0; i < 6; i++)
        fwrite(&num[i], sizeof(int), 1, file);

    fclose(file);
    negativeToEndFile(filename);
    file = fopen(filename, "rb");
    int res[6];
    int exp[6] = {8, 7, 9, -2, -4, -1};
    for (int i = 0; i < 6; i++) {
        fread(&res[i], sizeof(int), 1, file);
        assert(res[i] == exp[i]);
    }

    fclose(file);
}

void test7(){
    test7_1();
    test7_2();
    test7_3();
}

//test
void test(){
    test1();
    test_convert_float();
    test3();
    test4();
    test5();
    test7();
}

int main() {
    test();

    return 0;
}