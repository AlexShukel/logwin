#include "curses.h"
#include "utils.h"
#include <stdarg.h>

void va_mvprintColorText(int y, int x, int color, const char *format,
                         va_list argptr) {
    attron(COLOR_PAIR(color));
    stdscr->_curx = x;
    stdscr->_cury = y;
    vwprintw(stdscr, format, argptr);
    attroff(COLOR_PAIR(color));
}

void mvprintColorText(int y, int x, int color, const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);

    va_mvprintColorText(y, x, color, format, argptr);

    va_end(argptr);
}
