#ifndef C_STRING__H
#define C_STRING__H
#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

#include <ctype.h>
#include <memory.h>


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
    if (*lhs == *rhs && *lhs != '\0')
        return strcmp_(lhs + 1, rhs + 1);
    return *lhs - *rhs;
}

char* copy(const char *beginSource, const char *endSource, char *beginDestination){
    size_t bites_amount = endSource - beginSource;
    memcpy(beginDestination, beginSource, bites_amount);

    return &beginDestination[bites_amount];
}

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)){
    while (beginSource != endSource){
        if (f(*beginSource)){
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }

    return beginDestination;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)){
    while (rbeginSource != rendSource){
        if (f(*rbeginSource)){
            *beginDestination = *rbeginSource;
            beginDestination++;
        }
        rbeginSource--;
    }

    return beginDestination;
}

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

//2
void  removeExtraSpaces(char *s) {
    char *destination = s;
    char *current = s + 1;

    while (*current != '\0') {
        if (!(isspace(*current) && isspace(*destination))) {
            destination++;
            *destination = *current;
        }

        current++;
    }

    destination++;
    *destination = '\0';
}

#endif //C_STRING__H
