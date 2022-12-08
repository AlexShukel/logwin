#include "utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MIN_SIZE 12
char specialCharacters[] = "!@#$%^&*()-+";
uint8_t passwordStrengthCriteria[NUMBER_OF_CRITERIA] = {
    PASSWORD_STRENGTH_LENGTH, PASSWORD_STRENGTH_DIGIT,
    PASSWORD_STRENGTH_LOWERCASE, PASSWORD_STRENGTH_UPPERCASE,
    PASSWORD_STRENGTH_SPECIAL};

bool containsSpecifiedChar(const char *password,
                           int (*isSpecifiedChar)(int c)) {
    int i = 0;
    while (password[i] != '\0') {
        if (isSpecifiedChar(password[i])) {
            return true;
        }
        ++i;
    }

    return false;
}

bool containsDigit(const char *password) {
    return containsSpecifiedChar(password, isdigit);
}

bool containsLowercaseChar(const char *password) {
    return containsSpecifiedChar(password, islower);
}

bool containsUppercaseChar(const char *password) {
    return containsSpecifiedChar(password, isupper);
}

int isSpecialChar(int c) {
    int i = 0;
    while (specialCharacters[i] != '\0') {
        if (specialCharacters[i] == c) {
            return true;
        }
        ++i;
    }

    return false;
}

bool containsSpecialChar(const char *password) {
    return containsSpecifiedChar(password, isSpecialChar);
}

/*
This function checks if password is strong enough by the following criteria:
    1. Its length is at least 12.
    2. It contains at least one digit.
    3. It contains at least one lowercase English character.
    4. It contains at least one uppercase English character.
    5. It contains at least one special character. The special characters are:
!@#$%^&*()-+

Return value is an 8-bit flag, where ones determine unmet criterion from right
to left. For example: 0000 1010 means that criteria 2 and 4 was not met
*/
uint8_t isStrongPassword(const char *password) {
    size_t size = strlen(password);
    uint8_t bitFlag = 0;

    if (size < MIN_SIZE) {
        bitFlag ^= PASSWORD_STRENGTH_LENGTH;
    }

    if (!containsDigit(password)) {
        bitFlag ^= PASSWORD_STRENGTH_DIGIT;
    }

    if (!containsLowercaseChar(password)) {
        bitFlag ^= PASSWORD_STRENGTH_LOWERCASE;
    }

    if (!containsUppercaseChar(password)) {
        bitFlag ^= PASSWORD_STRENGTH_UPPERCASE;
    }

    if (!containsSpecialChar(password)) {
        bitFlag ^= PASSWORD_STRENGTH_SPECIAL;
    }

    return bitFlag;
}

char *strPasswordStrengthError(uint8_t errorNo) {
    char *msg;
    static char errorMsg[128];

    switch (errorNo) {
    case PASSWORD_STRENGTH_LENGTH: {
        strcpy(errorMsg, "Password length must be at least 12.");
        break;
    }

    case PASSWORD_STRENGTH_DIGIT: {
        strcpy(errorMsg, "Password must contain at least one digit.");
        break;
    }

    case PASSWORD_STRENGTH_LOWERCASE: {
        strcpy(errorMsg,
               "Password must contain at least one lowercase character.");
        break;
    }

    case PASSWORD_STRENGTH_UPPERCASE: {
        strcpy(errorMsg,
               "Password must container at least one uppercase character.");
        break;
    }

    case PASSWORD_STRENGTH_SPECIAL: {
        strcpy(errorMsg, "Password must contain at least one special character "
                         "(one of !@#$%^&*()-+).");
        break;
    }

    default:
        errorMsg[0] = '\0';
        break;
    }

    msg = errorMsg;
    return msg;
}
