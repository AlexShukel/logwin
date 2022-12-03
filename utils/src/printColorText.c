#include "curses.h"
#include "utils.h"
#include <stdarg.h>

void printColorText(int color, const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);

    attron(COLOR_PAIR(color));
    vwprintw(stdscr, format, argptr);
    attroff(COLOR_PAIR(color));

    va_end(argptr);
}