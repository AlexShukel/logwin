#include "curses.h"

void enableKeypad() {
    /* enable pressing arrow key to generate KEY_xxx codes */
    keypad(stdscr, TRUE);

    /* make getch wait sometime before returning ERR when no key is pressed */
    timeout(100);

    /* do not display pressed key */
    noecho();
}