#ifndef UTILS_H
#define UTILS_H

#define ERROR_TEXT_COLOR 1

#include <stdbool.h>
#include <stdlib.h>

// Manipulations with screen
void inputString(char *str, size_t size);
void printErrorMessage(int y, int x, char *message);
void clearLine(int y, int x);

// General utils
bool fileExists(char *fileName);

#endif