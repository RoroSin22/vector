#include "libs/vector.h"
//Тесты функций
void test_pushBackVector_emptyVector() {

    vector v = createVector(5);

    pushBack(&v,10);

    printf("pushBack_emptyVector :%d\n", v.data[0]);

}

void test_pushBackVector_fullVector(){

    vector v = createVector(5);

    v.size = 5;
    v.data[0] = 20;
    v.data[1] = 20;
    v.data[2] = 20;
    v.data[3] = 20;
    v.data[4] = 20;

    pushBack(&v, 21);

    printf("\n pushBack_fullVector: %d\n", v.data[5]);

}


void test_atVector_notEmptyVector() {

    vector v = createVector(5);

    v.size = 4;
    v.data[0] = 20;
    v.data[1] = 21;
    v.data[2] = 22;
    v.data[3] = 23;

    printf("\n atVector_notEmptyVector address: %x \n", atVector(&v, 2));
    printf("\n atVector_notEmptyVector value: %d \n", *atVector(&v, 2));
}

void test_atVector_requestToLastElement(){

    vector v = createVector(5);

    v.size = 3;
    v.data[0] = 20;
    v.data[1] = 20;
    v.data[2] = 20;
//Вывод в 16ричной с\с чтобы посмотреть нормально адрес
    printf("\n requestToLastElement address: %x \n", atVector(&v, 2));
    printf("\n requestToLastElement value: %d \n", *atVector(&v, 2));
}

void test_back_oneElementInVector(){

    vector v = createVector(5);

    v.size = 1;
    v.data[0] = 20;
//Вывод в 16ричной с\с чтобы посмотреть нормально адрес
    printf("\n back_oneElementInVector address: %x \n", back(&v));
    printf("\n back_oneElementInVector value: %d \n", *back(&v));
}

void test_front_oneElementInVector() {

    vector v = createVector(5);

    v.size = 1;
    v.data[0] = 20;
//Вывод в 16ричной с\с чтобы посмотреть нормально адрес
    printf("\n front_oneElementInVector address: %x \n", front(&v));
    printf("\n front_oneElementInVector value: %d \n", *front(&v));
}
int main() {

    test_pushBackVector_emptyVector();
    test_pushBackVector_fullVector();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
    test_back_oneElementInVector();
    test_front_oneElementInVector();

    return 0;
}