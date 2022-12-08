#include "curses.h"
#include "utils.h"
#include <stdbool.h>

int max(int a, int b) { return a > b ? a : b; }

void inputString(char *str, size_t size, bool noEcho) {
    if (noEcho) {
        noecho();
    }

    int currentY = stdscr->_cury, currentX = stdscr->_curx;

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
            currentX = max(0, currentX - 1);
            mvdelch(currentY, currentX);
            continue;
        }

        if (noEcho) {
            mvprintw(currentY, currentX, "*");
        }

        ++currentX;
        str[i] = ch;
        ++i;

        if (i >= size - 1) {
            break;
        }
    }

    str[i] = '\0';
    echo();

    if (noEcho) {
        clearLine(currentY, currentX);
    }
}