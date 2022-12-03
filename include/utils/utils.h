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
void mvprintColorText(int y, int x, int color, const char *format, ...);
void printErrorMessage(const char *message);
void mvprintErrorMessage(int y, int x, const char *message);
void clearLine(int y, int x);

// General utils
bool fileExists(char *fileName);
void nullifyString(char *str, size_t capacity);

#endif
