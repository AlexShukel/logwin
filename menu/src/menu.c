#include "app.h"
#include "curses.h"
#include "menu.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void printMenuOptions(char **menuOptions, size_t menuSize, int selectedItem,
                      int firstLine) {
    for (int i = 0; i < menuSize + 1; ++i) {
        short textColor =
            selectedItem == i ? GREEN_TEXT_COLOR : DEFAULT_TEXT_COLOR;

        mvprintColorText(firstLine + i, 0, textColor, "%s",
                         i == menuSize ? "Exit" : menuOptions[i]);
    }

    printw("\n");
}

int showMenu(char *menuTitle, char **menuOptions, size_t menuSize,
             char *inputMessage) {

    printw("%s\n", inputMessage);
    printw("%s\n", menuTitle);

    int firstOptionLine = stdscr->_cury;

    printMenuOptions(menuOptions, menuSize, 0, firstOptionLine);

    /* enable pressing arrow key to generate KEY_xxx codes */
    keypad(stdscr, TRUE);

    /* make getch wait sometime before returning ERR when no key is pressed */
    timeout(100);

    /* do not display pressed key */
    noecho();

    int selected = 0;

    while (1) {
        int ch = getch();

        if (ERR == ch) {
            continue;
        }

        if (KEY_UP == ch) {
            if (selected == 0) {
                selected = menuSize;
            } else {
                --selected;
            }

            printMenuOptions(menuOptions, menuSize, selected, firstOptionLine);

            continue;
        }

        if (KEY_DOWN == ch) {
            if (selected == menuSize) {
                selected = 0;
            } else {
                ++selected;
            }

            printMenuOptions(menuOptions, menuSize, selected, firstOptionLine);

            continue;
        }

        if ('\n' == ch) {
            break;
        };
    }

    erase();
    keypad(stdscr, FALSE);
    echo();

    return selected;
}
