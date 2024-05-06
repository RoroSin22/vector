#ifndef C_STRING__H
#define C_STRING__H

#include <ctype.h>

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;

    return end - begin;
}

char* find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;

    return begin;
}

char* findNonSpace(char *begin){
    while (*begin != '\0' && isspace(*begin))
        begin++;

    return begin;
}

char* findSpace(char *begin){
    while (*begin != '\0' && !isspace(*begin))
        begin++;

    return begin;
}

char* findNonSpaceReverse(char *rbegin, const char *rend){
    while (*rbegin != *rend && isspace(*rbegin))
        rbegin--;

    return rbegin;
}

char* findSpaceReverse(char *rbegin, const char *rend){
    while (*rbegin != *rend && !isspace(*rbegin))
        rbegin--;

    return rbegin;
}

int strcmp_(const char *lhs, const char *rhs){
    size_t len_dif = strlen_(lhs) < strlen_(rhs) ? strlen_(rhs) - strlen_(lhs) : strlen_(lhs) - strlen_(rhs);
    return len_dif == 0 ? 0 : lhs[len_dif - 1] - rhs[len_dif - 1];
}

#endif //C_STRING__H
