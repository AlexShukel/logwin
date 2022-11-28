#include "curses.h"
#include "utils.h"

static inline int max(int a, int b) { return a > b ? a : b; }

void inputString(char *str, size_t size) {
    int i = 0;
    while (1) {
        int ch = getch();

        if (ch == ERR) {
            continue;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\b') {
            i = max(0, i - 1);
            mvdelch(stdscr->_cury, stdscr->_curx);
            continue;
        }

        str[i] = ch;
        ++i;

        if (i >= size - 1) {
            break;
        }
    }

    str[i] = '\0';
}