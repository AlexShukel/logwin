#include "app.h"
#include "curses.h"
#include "utils.h"
#include <stdarg.h>

void printErrorMessage(const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);

    va_printColorText(ERROR_TEXT_COLOR, format, argptr);

    va_end(argptr);
}
