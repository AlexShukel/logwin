#include "app.h"
#include "curses.h"
#include "utils.h"

void printErrorMessage(const char *message) {
    printColorText(ERROR_TEXT_COLOR, message);
}
