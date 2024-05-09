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

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

BagOfWords _bag;
BagOfWords _bag2;


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

char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (isspace(*rbegin) && rbegin <= rend) {
        rbegin--;
    }
    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend) {
    while (!isspace(*rbegin) && rbegin != rend) {
        rbegin--;
    }
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

int getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {
    word->end = findNonSpaceReverse(rbegin, rend);

    if (word->end == rend)
        return 0;

    word->begin = findSpaceReverse(rbegin - 1, rend);

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

//6
void passWordPosition(WordDescriptor* w1, WordDescriptor* w2){
    w1->begin = w2->begin;
    w1->end = w2->end;
}
int areWordsEqual(WordDescriptor w1, WordDescriptor w2){
    char *w1_letter = w1.begin;
    char *w2_letter = w2.begin;

    while (w1_letter < w1.end && w2_letter < w2.end && *w1_letter == *w2_letter) {
        w1_letter++;
        w2_letter++;
    }

    return *w1_letter - *w2_letter;
}

bool areByAlphabet(char* str){
    WordDescriptor first_word;
    WordDescriptor second_word;

    if (getWord(str, &first_word)) {
        while (getWord(first_word.end, &second_word)) {
            if (areWordsEqual(first_word, second_word) > 0)
                return 0;
            passWordPosition(&first_word, &second_word);
        }
    }

    return 1;
}

//7
void getBagOfWords(BagOfWords *bag, char *s){
    WordDescriptor word = {s, s};
    size_t word_index = 0;
    bag->size = 0;

    while(getWord(word.end, &word)){
        passWordPosition(&bag->words[word_index], &word);
        word_index++;
        bag->size++;
    }
}

void outputWord(WordDescriptor word){
    int word_size = word.end - word.begin;
    printf("\"");
    for (int i = 0; i < word_size; i++)
        printf("%c", word.begin[i]);
    printf("\" ");
}

void outputBagOfWords(BagOfWords bag, char *s){
    getBagOfWords(&bag, s);
    for (int i = 0; i < bag.size; i++)
        outputWord(bag.words[i]);
}

void outputWordsInString(char *s){
    outputBagOfWords(_bag, s);
}

//8

bool isPalindrome(WordDescriptor word){
    char* left_letter = word.begin;
    char* right_letter = word.end - 1;
    while (left_letter < right_letter){
        if(*left_letter != *right_letter)
            return 0;
        left_letter++;
        right_letter--;
    }
    return 1;
}

int countPalindromes(char* str){
    WordDescriptor word = {str, str};
    int counter = 0;

    while(getWord(word.end, &word))
        counter += isPalindrome(word);

    return counter;
}

//9
void combinedSting(char* s1, char* s2, char* res){
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    char* current = res;

    while ((isW1Found = getWord(beginSearch1, &word1)),
            (isW2Found = getWord(beginSearch2, &word2)),
            isW1Found || isW2Found) {
        if (isW1Found){
            copy(word1.begin, word1.end, current);
            current += word1.end - word1.begin;
            *current = ' ';
            current++;
            beginSearch1 = word1.end;
        }
        if (isW2Found){
            copy(word2.begin, word2.end, current);
            current += word2.end - word2.begin ;
            *current = ' ';
            current++;
            beginSearch2 = word2.end;
        }
    }
    current--;
    *current = '\0';
}

//10
/*void reverseWordsInString(char* str){
    copy(str, str + strlen_(str), _stringBuffer);
    WordDescriptor word;

    char* current = str;

    while (getWordReverse(word.begin, _stringBuffer, &word)){
        copy(word.begin, word.end, current);
        current += word.end - word.begin;
        *current = ' ';
        current++;
    }

    *current = '\0';
    replace(str, "  ", " ");
}*/

//11
bool checkLetter(char* letter_in_word, char letter){
    return *letter_in_word == letter || *letter_in_word == letter - 32;
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w){
    WordDescriptor first_word;
    WordDescriptor second_word;
    if(getWord(s, &first_word)){
        if(*first_word.begin != 'a' && *first_word.begin != 'A') {
            while(getWord(first_word.end, &second_word)){
                if (checkLetter(second_word.begin, 'a')){
                    passWordPosition(w, &first_word);
                    return WORD_FOUND;
                }
                passWordPosition(&first_word, &second_word);
            }

            return NOT_FOUND_A_WORD_WITH_A;
        }

        return FIRST_WORD_WITH_A;
    }

    return EMPTY_STRING;
}

//12
void wordDescriptorToString(WordDescriptor word, char *destination){
    copy(word.begin, word.end, destination);
}

WordDescriptor lastWordFromFirst(char* str1, char* str2){
    getBagOfWords(&_bag, str1);
    getBagOfWords(&_bag2, str2);

    for (int i = _bag.size - 1; i >= 0; i--){
        for (int j = 0; j < _bag2.size; j++){
            if(areWordsEqual(_bag.words[i], _bag2.words[j]) == 0)
                return _bag.words[i];
        }
    }
    WordDescriptor word = {NULL, NULL};
    return word;
}

//13

bool areEqualWordInString(char* str){
    getBagOfWords(&_bag, str);

    for (int i = 0; i < _bag.size; i++){
        for (int j = i + 1; j < _bag.size; j++){
            if (areWordsEqual(_bag.words[i], _bag.words[j]) == 0)
                return 1;
        }
    }

    return 0;
}

#endif //C_STRING__H
