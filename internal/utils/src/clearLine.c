#include "curses.h"
#include "utils.h"

void clearLine(int y) {
    mvdeleteln(y, 0);
    mvinsertln(y, 0);
}
