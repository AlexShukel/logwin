#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>

#define DEFAULT_TEXT_COLOR 0
#define ERROR_TEXT_COLOR 1
#define GREEN_TEXT_COLOR 2

// Manipulations with screen
void inputString(char *str, size_t size);
void printErrorMessage(int y, int x, char *message);
void clearLine(int y, int x);

// General utils
bool fileExists(char *fileName);

#endif
