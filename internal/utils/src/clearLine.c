#include "curses.h"
#include "utils.h"

void clearLine(int y, int x) {
    mvdeleteln(y, x);
    mvinsertln(y, x);
}
