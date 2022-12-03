#ifndef UTILS_H
#define UTILS_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


// Manipulations with screen
void inputString(char *str, size_t size);
void printColorText(int y, int x, int color, const char *format, ...);
void printErrorMessage(int y, int x, char *message);
void clearLine(int y, int x);

// General utils
bool fileExists(char *fileName);
uint64_t getElementsSize(FILE *file);
void nullifyString(char *str, size_t capacity);

#endif
