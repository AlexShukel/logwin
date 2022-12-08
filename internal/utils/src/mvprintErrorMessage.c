#include "app.h"
#include "curses.h"
#include "utils.h"
#include <stdarg.h>

void mvprintErrorMessage(int y, int x, const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);

    va_mvprintColorText(y, x, ERROR_TEXT_COLOR, format, argptr);

    va_end(argptr);
}
