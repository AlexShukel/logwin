#include "app.h"
#include "curses.h"
#include "menu.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>

void printMenuOptions(char **menuOptions, size_t menuSize, int selectedItem,
                      int firstLine) {
    for (int i = 0; i < menuSize; ++i) {
        short textColor =
            selectedItem == i ? GREEN_TEXT_COLOR : DEFAULT_TEXT_COLOR;

        mvprintColorText(firstLine + i, 0, textColor, "%d: %s", i + 1,
                         menuOptions[i]);
    }

    printw("\n");
}

int showMenu(char *menuTitle, char **menuOptions, size_t menuSize,
             char *inputMessage) {

    printw("%s\n", inputMessage);
    printw("%s\n", menuTitle);

    int firstOptionLine = stdscr->_cury;

    printMenuOptions(menuOptions, menuSize, 0, firstOptionLine);

    enableKeypad();

    int selected = 0;

    while (1) {
        int ch = getch();

        if (ERR == ch) {
            continue;
        }

        selected = handleSelectedChange(ch, selected, menuSize);

        if ('\n' == ch) {
            break;
        };

        printMenuOptions(menuOptions, menuSize, selected, firstOptionLine);
    }

    erase();
    disableKeypad();

    return selected;
}
