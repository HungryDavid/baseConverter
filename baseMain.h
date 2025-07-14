#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h> 

#define MAX_VAL 65 //64 bits, its 65 because of null byte

void askBaseFrom(int* baseFrom);
unsigned long long askVal(int *baseFrom, char prevVal[]);
int isValidCharForBase(char character, int baseNum);
int maxDigitsForBase(int baseNum);
int charToDigit(char c);
int safeBaseToDecimal(const char *input, int baseNum, unsigned long long *result);
void askBaseTo(int* baseFrom, int* baseTo);
void decimalToBase(unsigned long long decVal, int baseTo, char newVal[]);