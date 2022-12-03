#ifndef UTILS_H
#define UTILS_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Manipulations with screen
void inputString(char *str, size_t size);

void printColorText(int color, const char *format, ...);
void va_printColorText(int color, const char *format, va_list argptr);
void mvprintColorText(int y, int x, int color, const char *format, ...);
void va_mvprintColorText(int y, int x, int color, const char *format,
                         va_list argptr);

void printErrorMessage(const char *format, ...);
void mvprintErrorMessage(int y, int x, const char *format, ...);

void clearLine(int y, int x);

// General utils
bool fileExists(char *fileName);
void nullifyString(char *str, size_t capacity);

// Strong password module
#define PASSWORD_STRENGTH_LENGTH 0b00000001
#define PASSWORD_STRENGTH_DIGIT 0b00000010
#define PASSWORD_STRENGTH_LOWERCASE 0b00000100
#define PASSWORD_STRENGTH_UPPERCASE 0b00001000
#define PASSWORD_STRENGTH_SPECIAL 0b00010000
#define NUMBER_OF_CRITERIA 5

extern uint8_t passwordStrengthCriteria[NUMBER_OF_CRITERIA];

uint8_t isStrongPassword(const char *password);
char *strPasswordStrengthError(uint8_t errorNo);

#endif
