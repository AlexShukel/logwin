#include "app.h"
#include "curses.h"
#include "utils.h"

void printErrorMessage(int y, int x, char *message) {
    printColorText(y, x, ERROR_TEXT_COLOR, message);
}
