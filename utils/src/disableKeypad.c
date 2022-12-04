#include "curses.h"

void disableKeypad() {
    keypad(stdscr, FALSE);
    echo();
}