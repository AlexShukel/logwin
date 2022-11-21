#include "curses.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    initscr();

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    start_color();

    printw("Welcome to logwin!\n");

    char loginOption[] = "Login";
    char singUpOption[] = "Sign up";
    char *options[] = {loginOption, singUpOption};
    int selected = showMenu("Authentication options:", options, 2,
                            "Login to existing account or create a new one.");

    printf("%d\n", selected);

    endwin();
    return 0;
}
