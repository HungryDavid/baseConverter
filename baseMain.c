#include "baseMain.h"
#include "baseFunctions.c"


int main(){
  //function to ask user the number to be converted to
  //function to ask for base to convert from
  //function to check if the number given matches with the given baseFrom  
  //function to ask for base to convert to
  //function/s to convert from base  2-3-5-8-10-12
  int baseFrom = 0; //holds the original base of the number
  int baseTo = 0; //holds the new base of the number
  char prevVal[MAX_VAL];//holds the original value of the number
  unsigned long long decVal; //holds the decimal value of the number
  char newVal[MAX_VAL]; //holds the new value of the number
  askBaseFrom(&baseFrom); 
  decVal = askVal(&baseFrom, prevVal);
  askBaseTo(&baseFrom, &baseTo);
  decimalToBase(decVal, baseTo, newVal);
  printf("Converted value (%s) from base %d to base %d: %s\n", prevVal, baseFrom, baseTo, newVal);

  return 0;
}