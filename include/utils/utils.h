/**
 * @author Aleksandras Sukelovic <alex.shukel@gmail.com>
 * @version 1.0.0
 *
 * Logwin app general definitions
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Function to input string from keyboard. Reads maximum size characters and
// writes null terminating character in the end.
void inputString(char *str, size_t size, bool noEcho);

// Function to modify given string from keyboard. Reads maximum size characters
// and writes null terminating character in the end.
void modifyString(char *str, size_t size);

// Function to print colored text.
void printColorText(int color, const char *format, ...);
void va_printColorText(int color, const char *format, va_list argptr);

// Function to print colored text in specified coordinates.
void mvprintColorText(int y, int x, int color, const char *format, ...);
void va_mvprintColorText(int y, int x, int color, const char *format,
                         va_list argptr);

// Function to print red error message.
void printErrorMessage(const char *format, ...);
// Function to print red error message in specified coordinates.
void mvprintErrorMessage(int y, int x, const char *format, ...);

// Function to clear line in specified y coordinate.
void clearLine(int y);

void enableKeypad();
void disableKeypad();

// Function to check if specified file exists.
bool fileExists(char *fileName);

// Function to fill the rest of the string with 0.
void nullifyString(char *str, size_t capacity);

// Function to check if stirng contains slashes ('\' or '/').
bool includesSlashes(const char *str);

// Function to get maximum value of two integers.
int max(int a, int b);

// ---------------------------------------------
// Bit map codes for different validation errors
// ---------------------------------------------

#define PASSWORD_STRENGTH_LENGTH 0b00000001
#define PASSWORD_STRENGTH_DIGIT 0b00000010
#define PASSWORD_STRENGTH_LOWERCASE 0b00000100
#define PASSWORD_STRENGTH_UPPERCASE 0b00001000
#define PASSWORD_STRENGTH_SPECIAL 0b00010000
#define NUMBER_OF_CRITERIA 5

extern uint8_t passwordStrengthCriteria[NUMBER_OF_CRITERIA];

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
uint8_t isStrongPassword(const char *password);

// Prints password strength error according to isStrongPassword description.
char *strPasswordStrengthError(uint8_t errorNo);

#endif
