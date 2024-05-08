#ifndef C_STRING__H
#define C_STRING__H
#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)
#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20
#define NUMBER_SYMBOL 48

#include <ctype.h>
#include <memory.h>

char _stringBuffer[MAX_STRING_SIZE + 1];


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
    while (beginSource <= endSource){
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
        if (!(isspace(*current) && isspace(*destination))){
            destination++;
            *destination = *current;
        }

        current++;
    }

    destination++;
    *destination = '\0';
}

//3
typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

bool getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;

    word->end = findSpace(word->begin);
    return 1;
}

void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,_stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,_stringBuffer - 1,word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitsToEndWord(WordDescriptor word){
    char *endStringBuffer = copy(word.begin, word.end,_stringBuffer);
    char *recPosition = copyIf(_stringBuffer,endStringBuffer,word.begin, isalpha);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isdigit);
}

void digitsToEndWordInSentence(char* s){
    char *beginSearch = s;
    WordDescriptor word;
    while (getWord(beginSearch, &word)) {
        digitsToEndWord(word);
        beginSearch = word.end;
    }
}

bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word){
    word->begin = findNonSpaceReverse(rbegin, rend);
    if (*word->begin == '\0')
        return 0;

    word->end = findSpaceReverse(word->begin, rend);
    return 1;
}

//4
void numbersToSpaces(char* source,  char* s){
    char* source_end = source + strlen_(source);
    char *buffer_end = copy(source, source_end, _stringBuffer);
    char *buffer = _stringBuffer;

    while (buffer != buffer_end){
        if(isdigit(*buffer)){
            for (int i = 0; i < *buffer - NUMBER_SYMBOL; i++){
                *s = ' ';
                s++;
            }
        } else{
            *s = *buffer;
            s++;
        }
        buffer++;
    }
    *s = '\0';
}

//5
char* getEndOfString(char* source){
    return source + strlen_(source);
}

bool wordcmp(char* w1, char* w2){
    while(*w1 != '\0'){
        if (*w1 != *w2)
            return 0;
        w1++;
        w2++;
    }
    return 1;
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};

    char *readPtr, *recPtr;
    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        char* last_symbol = copy(source, getEndOfString(source), _stringBuffer);
        *last_symbol = '\0';
        readPtr = _stringBuffer;
        recPtr = source;
    }

    while (*readPtr != '\0') {
        if (wordcmp(w1, readPtr)) {
            copy(word2.begin, word2.end, recPtr);
            readPtr += w1Size;
            recPtr += w2Size;
        } else {
            *recPtr = *readPtr;
            readPtr++;
            recPtr++;
        }
    }

    *recPtr = '\0';
}
#endif //C_STRING__H
