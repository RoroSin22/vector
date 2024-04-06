#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned int set;
//Универсом
set u = {0,1,2,3,4,5,6,7};
/*Выбрано от 0 до 7 включительно, т.к
 * в формуле 2^n, где n - кол-во вариантов.
 * Следовательно, универмом будет 2^3 = 8, а
 * мощность каждого множества 2^(n-1)*/

set tmv1(set a, set b, set c) {
    set act1 = ~b;
    set act2 = act1 & a;
    set act3 = act2 ^ b;
    set nc = ~c;
    set act4 = nc - act3;
    set act5 = nc - act4;
    return act5;
}

set tmv2(set a, set b, set c) {
    set act1 = a | b;
    set act2 = c & a;
    set act3 = c ^ act1;
    set act4 = act3 ^ act2;
    return act4;
}

set tmv3(set a, set b, set c) {
    set act1 = a - c;
    set act2 = c - a;
    set act3 = act2 | b;
    set act4 = act1 & act3;
    return act4;
}

set tmv4(set a, set b, set c) {
    set na = ~a;
    set nb = ~b;
    set nc = ~c;
    set act1 = na | b;
    set act2 = act1 & nb;
    set act3 = act2 | nc;
    set act4 = a | b;
    set act5 = act4 & act3;
    return act5;
}

set tmv5(set a, set b, set c) {
    set nc = ~c;
    set act1 = a & b;
    set act2 = ~act1;
    set act3 = act2 & c;
    set act4 = a & nc;
    set act5 = act3 | act4;
    return act5;
}

void Set_theoretic_method() {
    bool identities[5][5] = {0};
    memset(identities, 1, sizeof(identities));
    for (size_t i = 0; i < 5; i++)
        identities[i][i] = false;

    set a = {{ 1, 3, 5, 7 }, &u};;
    set b = {{ 2, 3, 6, 7 }, &u};
    set c = {{ 4, 5, 6, 7 }, &u};

    set act1 = tmv1(a, b, c);
    set act2 = tmv2(a, b, c);
    set act3 = tmv3(a, b, c);
    set act4 = tmv4(a, b, c);
    set act5 = tmv5(a, b, c);

    set sets[] = {act1, act2, act3, act4, act5};
    for (size_t i = 0; i < 5; i++)
        for (size_t j = 0; j < 5; j++)
            if (sets[i] != sets[j])
                identities[i][j] = false;

    for (size_t i = 0; i < 5; i++)
        for (size_t j = 0; j < 5; j++)
            if (identities[i][j])
                printf("%zu %zu\n", i + 1, j + 1);
}

int main() {
    Set_theoretic_method();
    return 0;
}