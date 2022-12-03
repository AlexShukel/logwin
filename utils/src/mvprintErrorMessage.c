#include "app.h"
#include "curses.h"
#include "utils.h"

void mvprintErrorMessage(int y, int x, const char *message) {
    mvprintColorText(y, x, ERROR_TEXT_COLOR, message);
}
