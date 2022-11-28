#include "app.h"
#include "curses.h"
#include "utils.h"


void printErrorMessage(int y, int x, char *message) {
    attron(COLOR_PAIR(ERROR_TEXT_COLOR));
    mvprintw(y, x, message);
    attroff(COLOR_PAIR(ERROR_TEXT_COLOR));
}
