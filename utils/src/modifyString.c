#include "curses.h"
#include "utils.h"
#include <stdbool.h>

void modifyString(char *str, size_t size) {
    printw("%s", str);

    int i = stdscr->_curx;
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
            delch();
            continue;
        }

        str[i] = ch;
        ++i;

        if (i >= size - 1) {
            break;
        }
    }

    str[i] = '\0';
    echo();
}
