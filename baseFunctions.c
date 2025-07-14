/* function askBaseFrom gets the original base of the number from the user
@param baseFrom - stores the original base of the number
*/
void askBaseFrom(int* baseFrom){
  int validInput = 0;
  do {
    printf("What is your number's base?(2,3,5,8,10,16): ");
    validInput = scanf("%d", baseFrom);
    if(validInput != 1 || (*baseFrom != 2 && *baseFrom != 3 && *baseFrom != 5 && *baseFrom != 8 && *baseFrom != 10 && *baseFrom != 16)){
      while (validInput != 1) {
        while (scanf("%*s") != 0);
        printf("What is your number's base?(2,3,5,8,10,16): ");
        validInput = scanf("%d", baseFrom);
      }
    }
  } while (*baseFrom != 2 && *baseFrom != 3 && *baseFrom != 5 && *baseFrom != 8 && *baseFrom != 10 && *baseFrom != 16); 
}

/* function askVal gets the validated value from the user
@param baseFrom - stores the original base of the number
@prevVal[] - stores the validated value from the user
@return - returns the decimal value of the validated value 
*/
unsigned long long askVal(int *baseFrom, char prevVal[]){
  int validInput = 0;
  int isValid;
  unsigned long long decimalValue;
  int valLength = maxDigitsForBase(*baseFrom);
  printf("Enter your value in base %d only up to %d digits: ", *baseFrom, valLength);
  scanf("%s", prevVal);
  while (validInput == 0){
    isValid = 1;
    for (int i = 0; prevVal[i] != '\0'; i++) {
    if (isValidCharForBase(prevVal[i], *baseFrom) == 0) {
      isValid = 0;
      break;
        }
      }
    if (isValid && strlen(prevVal) > valLength) {
      isValid = 0;
    }
    if (isValid == 1) {  
      if (safeBaseToDecimal(prevVal, *baseFrom, &decimalValue) == 0) {
        isValid = 0;
      } 
    }
    if (isValid == 1) {
      validInput = 1;
    } 
    else {
      printf("Invalid input for base %d.\n Please enter your value again (only %d digits): ", *baseFrom, valLength);
      scanf("%s", prevVal);
    }
  }
  return decimalValue;
}

/* function isValidCharForBase checks if the value is valid for its base number
@param baseNum - stores the original base of the number
@param char - holds a character value from the value
*/
int isValidCharForBase(char character, int baseNum) {
  int returnVal = 0;
    if (isdigit(character)) {//checks if the character is a digit and if it's lower than the base number 
      returnVal = (character - '0') < baseNum;
    }
    if (isalpha(character)) {
      int value = toupper(character) - 'A' + 10;
      returnVal = value < baseNum;
    }
    return returnVal; // invalid character
}

/* function maxDigitsForBase checks how many digits should be allowed to be inputted by the user
@param baseFrom - stores the original base of the number
@return - returns the allowed input limit 
*/
int maxDigitsForBase(int baseNum) {
  int returnVal = 0;
  switch (baseNum) {
    case 2:
    case 3:
    case 5:
      returnVal = 8;  // allow up to 8 digits
      break;
    case 8:
    case 10:
      returnVal = 4;  // allow up to 4 digits
      break;
    default:
      returnVal = 2;  // allow up to 2 digits
      break;
  }
  return returnVal;
}

/* function charToDigit converts the characters into integers
@param c - stores the characters of the value
return - returns the converted character, else return -1
*/
int charToDigit(char c) {
    if (isdigit(c)) return c - '0';
    if (isalpha(c)) return toupper(c) - 'A' + 10;
    return -1;
}

/* function safeBaseToDecimal checks if the given value can be converted into decimal base
@param input - stores the value given by the player
@param baseNum - holds the original base number
@param result - stores the decimal value
@return - returns 1 if converted, else return 0
*/
int safeBaseToDecimal(const char *input, int baseNum, unsigned long long *result) {
  int returnVal = 1;
  *result = 0;
  unsigned long long maxDiv = ULLONG_MAX / baseNum;
  unsigned long long maxMod = ULLONG_MAX % baseNum;
  int digit;

  for (int i = 0; input[i]; i++) {
    digit = charToDigit(input[i]);
    if (digit < 0 || digit >= baseNum){ 
      returnVal = 0;
      break;
    }
    if (*result > maxDiv || (*result == maxDiv && digit > maxMod)) {
      returnVal = 0;
      break;
    }
    *result = (*result * baseNum) + digit;
  }
  return returnVal; // success
}

/* function askBaseFrom gets the new base of the number from the user
@param baseFrom - stores the original base of the number
@param baseTo - stores the new base of the number
*/
void askBaseTo(int* baseFrom, int* baseTo){
  int validInput = 0;
  do {
    printf("What base do you want your number to be converted into?(2,5,8,10,16): ");
    validInput = scanf("%d", baseTo);
    if(validInput != 1 || (*baseTo != 2 && *baseTo != 5 && *baseTo != 8 && *baseTo != 10 && *baseTo != 16) || *baseFrom == *baseTo){
      while (validInput != 1) {
        while (scanf("%*s") != 0);
        printf("What base do you want your number to be converted into?(2,5,8,10,16): ");
        validInput = scanf("%d", baseTo);
      }
      while(*baseFrom == *baseTo){
        printf("Warning: The base you want it to be converted into must not be the original base of your number!\n");
        printf("What base do you want your number to be converted into?(2,5,8,10,16): ");
        validInput = scanf("%d", baseTo);
      }
    }
  } while (*baseTo != 2 && *baseTo != 5 && *baseTo != 8 && *baseTo != 10 && *baseTo != 16); 

}

/* function decimalToBase converts the decimal value into the desried base value of the player
@param decVal - stores the decimal value
@param baseTo - holds the new base of the number
@param newVal - holds the new value 
*/
void decimalToBase(unsigned long long decVal, int baseTo, char newVal[]) {
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buffer[65]; // enough for 64 binary digits + null
    int i = 0;
    if(baseTo == 10){
      sprintf(newVal, "%llu", decVal);
      return;
    }
    if (decVal == 0) {
        newVal[0] = '0';
        newVal[1] = '\0';
        return;
    }

    while (decVal > 0) {
        buffer[i++] = digits[decVal % baseTo];
        decVal /= baseTo;
    }

    // Reverse the string into result
    for (int j = 0; j < i; j++) {
        newVal[j] = buffer[i - j - 1];
    }
    newVal[i] = '\0'; // null-terminate
}

