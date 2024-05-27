#include "libs/matrix.h"
#include "libs/string_.h"

//1
void matrixToZero(matrix m){
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++)
            m.values[i][j] = 0;
    }
}

matrix addOnes(int n, int* query[], int operations){
    matrix m = getMemMatrix(n, n);
    matrixToZero(m);

    for (int i = 0; i < operations; i++){
        int begin_row = query[i][0];
        int begin_col = query[i][1];
        int end_row = query[i][2];
        int end_col = query[i][3];

        for (int j = begin_row; j <= end_row; j++){
            for (int k = begin_col; k <= end_col; k++)
                m.values[j][k] += 1;
        }
    }

    return m;
}

void test_task1(){
    int operation1[4] = {1,1,2,2};
    int operation2[4] = {0,0,1,1};
    int* query[2] = {operation1, operation2};
    matrix res = addOnes(3, query, 2);
    matrix exp = createMatrixFromArray((int[]) {
                                               1, 1, 0,
                                               1, 2, 1,
                                               0, 1, 1},
                                       3, 3);
    assert(areTwoMatricesEqual(&res, &exp));
    freeMemMatrix(&res);
    freeMemMatrix(&exp);
}

//2
int countNeighbours(matrix m, int index_row, int index_col){
    int begin_row = index_row - 1 >= 0 ? index_row - 1 : index_row;
    int begin_col = index_col - 1 >= 0 ? index_col - 1 : index_col;
    int end_row = index_row + 1 < m.nRows ? index_row + 1 : index_row;
    int end_col = index_col + 1 < m.nCols ? index_col + 1 : index_col;

    int counter = 0;

    for (int j = begin_row; j <= end_row; j++) {
        for (int k = begin_col; k <= end_col; k++)
            counter += m.values[j][k];
    }

    return counter - m.values[index_row][index_col];
}

void gameOfLife(matrix m){
    matrix temp = getMemMatrix(m.nRows, m.nCols);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            temp.values[i][j] = m.values[i][j];
    }

    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            int neighbours = countNeighbours(temp, i, j);
            if (neighbours < 2 || neighbours > 3)
                m.values[i][j] = 0;
            else if (neighbours == 3)
                m.values[i][j] = 1;
        }
    }

    freeMemMatrix(&temp);
}

void test_task2(){
    matrix m = createMatrixFromArray((int[]) {
                                             0, 1, 0,
                                             0, 0, 1,
                                             1, 1, 1,
                                             0, 0, 0},
                                     4, 3);
    matrix res = createMatrixFromArray((int[]) {
                                             0, 0, 0,
                                             1, 0, 1,
                                             0, 1, 1,
                                             0, 1, 0},
                                     4, 3);
    gameOfLife(m);
    assert(areTwoMatricesEqual(&m, &res));
    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

//3
int compare (const void * a, const void * b){
    return ( *(int*)a - *(int*)b );
}

int getMedian(matrix m, int index_row, int index_col){
    int array_window[8];

    array_window[0] = m.values[index_row - 1][index_col - 1];
    array_window[1] = m.values[index_row - 1][index_col];
    array_window[2] = m.values[index_row - 1][index_col + 1];
    array_window[3] = m.values[index_row][index_col - 1];
    array_window[4] = m.values[index_row][index_col + 1];
    array_window[5] = m.values[index_row + 1][index_col - 1];
    array_window[6] = m.values[index_row + 1][index_col];
    array_window[7] = m.values[index_row + 1][index_col + 1];

    qsort(array_window, 8, sizeof(int), compare);

    return (array_window[3] + array_window[4]) / 2;
}

void medianFilter(matrix m){
    for(int i = 1; i < m.nRows - 1; i++){
        for(int j = 1; j < m.nCols - 1; j++)
            m.values[i][j] = getMedian(m, i, j);
    }

}

void test_task3(){
    matrix m = createMatrixFromArray((int[]) {
                                             10, 20, 30,
                                             25, 35, 45,
                                             15, 25, 35},
                                     3, 3);
    matrix res = createMatrixFromArray((int[]) {
                                             10, 20, 30,
                                             25, 25, 45,
                                             15, 25, 35},
                                     3, 3);
    medianFilter(m);
    assert(areTwoMatricesEqual(&m, &res));
    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

//4
typedef struct domain {
    int visits;
    char name[1024];
} domain;

int findDomain(const domain *results, int size, char *s) {
    for (int index = 0; index < size; index++) {
        if (strcmp(results[index].name, s) == 0)
            return index;
    }

    return size;
}

bool find_number_in_arr(int* array, int length, int num) {
    for (int index = 0; index < length; index++){
        if (num == array[index])
            return true;
    }
    return false;
}

void handlerDotPrtNotNull(domain* array, int index, char* dotPtr, domain* results, int* sizeResult) {
    strcpy(array[index].name, dotPtr + 1);
    int position = findDomain(results, *sizeResult, array[index].name);

    if (position == *sizeResult) {
        results[*sizeResult] = array[index];
        *sizeResult += 1;
    } else
        results[position].visits += array[index].visits;
}

void outputArraysDomains(domain *results, int size) {
    for (int index = 0; index < size; index++)
        printf("%d %s\n", results[index].visits, results[index].name);
}

void countInteractionsDomain(domain* arr, int size) {
    int close_index_size[size];
    int count_close = 0;
    domain results[1024];
    int size_res = 0;
    for (int ind = 0; ind < size; ind++)
        results[size_res++] = arr[ind];

    while (count_close != size) {
        for (int index = 0; index < size; index++) {
            if (!find_number_in_arr(close_index_size, count_close, index)) {
                char *dot_ptr;
                dot_ptr = strchr(arr[index].name, '.');

                if (dot_ptr != NULL)
                    handlerDotPrtNotNull(arr, index, dot_ptr, results, &size_res);
                else
                    close_index_size[count_close++] = index;
            }
        }
    }

    outputArraysDomains(results, size_res);
}

//5
int CountSubMatricesOnlyOnes(matrix m){
    int sum = 0;

    for (int i = 0; i < m.nRows; i++){
        int *nums = (int*) malloc(m.nCols * sizeof(int));
        for (int j = 0; j < m.nCols; j++){
            if (m.values[i][j] == 0)
                nums[j] = 0;
            else if (j == 0)
                nums[j] = 1;
            else{
                nums[j] = nums[j - 1] + 1;
                sum += nums[j - 1] + 1;
            }

            int min = INT_MAX;
            for (int k = j; k < m.nCols; k++)
                min = nums[k] < min ? nums[k] : min;
            sum += min;
        }
    }

    return sum;
}

void test_task_5_1() {
    matrix m = createMatrixFromArray((int[]) {
                                               1, 0, 1,
                                               1, 1, 0,
                                               1, 1, 0},
                                       3, 3);
    int answer = CountSubMatricesOnlyOnes(m);
    freeMemMatrix(&m);

    assert( answer == 13);

}

void test_task_5_2(){
    matrix m = createMatrixFromArray((int[]) {
                                               0, 0, 0,
                                               0, 0, 0},
                                       2, 3);
    int answer = CountSubMatricesOnlyOnes(m);
    freeMemMatrix(&m);

    assert(answer == 0);
}

void test_task_5() {
    test_task_5_1();
    test_task_5_2();
}

//6

void indexToNumberStr(const char *str, char *result) {
    char buff[10];
    int str_len = strlen(str);
    size_t buff_length = 0;
    size_t calculated_res_length = 0;
    char num = '1';

    for (size_t index = 0; index < str_len; index++) {
        buff[buff_length++] = num++;
        if (str[index] == 'I')
            while (buff_length > 0)
                result[calculated_res_length++] = buff[--buff_length];
    }
    buff[buff_length++] = num;
    while (buff_length > 0)
        result[calculated_res_length++] = buff[--buff_length];
    result[calculated_res_length] = '\0';
}

void test_task_6_1() {
    char s[10] = "IIIDIDDD";
    char res[10];

    indexToNumberStr(s, res);
    char answer[10] = "123549876";

    assert(strcmp(res, answer) == 0);
}

void test_task_6_2() {
    char s[5] = "DDD";
    char res[5];

    indexToNumberStr(s, res);
    char answer[10] = "4321";

    assert(strcmp(res, answer) == 0);
}

void test_task_6() {
    test_task_6_1();
    test_task_6_2();
}

//7

typedef struct branch {
    int value;
    struct branch* left;
    struct branch* right;
} branch;

branch* makeTree_(int *numbers, int left, int right) {
    if (left > right)
        return NULL;
    int max_index = left;
    for (int i = left; i <= right; i++)
        if (numbers[i] > numbers[max_index]) max_index = i;

    branch* root = (branch*)malloc(sizeof(branch));
    root->value = numbers[max_index];
    root->left = makeTree_(numbers, left, max_index - 1);
    root->right = makeTree_(numbers, max_index + 1, right);
    return root;
}

branch* makeTree(int* numbers, int numbers_size) {
    return makeTree_(numbers, 0, numbers_size - 1);
}

void print_tree(branch* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        print_tree(root->left);
        print_tree(root->right);
    } else
        printf("null ");
}


void test(){
    test_task1();
    test_task2();
    test_task3();
    test_task_5();
    test_task_6();
}

int main() {
    int numbers[6] = {3, 2, 1, 6, 0, 5};
    int len = 6;
    branch* res = makeTree(numbers, len);
    print_tree(res);

    return 0;
}