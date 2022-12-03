#include "curses.h"
#include "utils.h"
#include <stdarg.h>

void va_printColorText(int color, const char *format, va_list argptr) {
    attron(COLOR_PAIR(color));
    vwprintw(stdscr, format, argptr);
    attroff(COLOR_PAIR(color));
}

void printColorText(int color, const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);

    va_printColorText(color, format, argptr);

    va_end(argptr);
}