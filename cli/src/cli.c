#include "curses.h"
#include "menu.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME_LENGTH 255
#define PASSWORD_LENGTH 255

static inline int max(int a, int b) { return a > b ? a : b; }

void inputString(char *str) {
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
            mvdelch(stdscr->_cury, stdscr->_curx);
            continue;
        }

        str[i] = ch;
        ++i;
    }

    str[i] = '\0';
}

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
    int answer = showMenu("Authentication options:", options, 2,
                          "Login to existing account or create a new one.");

    echo();

    if (answer == 0) {
        // Login
        printw("Enter your username:\n");
    } else {
        // Sign up
        printw("New username:\n");
        char *newUsername = malloc(USERNAME_LENGTH);
        inputString(newUsername);

        // Disable echo for password input
        noecho();
        bool arePasswordSame = false;
        char *newPassword = malloc(PASSWORD_LENGTH);
        char *repeatedNewPassword = malloc(PASSWORD_LENGTH);
        init_pair(1, COLOR_RED, COLOR_BLACK);

        int currentLine = stdscr->_cury + 1;

        while (!arePasswordSame) {
            mvprintw(currentLine, 0, "New master password:\n");
            inputString(newPassword);

            mvprintw(currentLine + 2, 0, "Repeat you master password:\n");
            inputString(repeatedNewPassword);

            if (strcmp(newPassword, repeatedNewPassword) == 0) {
                arePasswordSame = true;
            } else {
                attron(COLOR_PAIR(1));
                mvprintw(currentLine - 1, 0,
                         "Master password does not match with repeated "
                         "password. Try again.\n");
                attroff(COLOR_PAIR(1));
            }
        }

        printf("%s\n%s\n", newUsername, newPassword);

        free(newUsername);
        free(newPassword);
    }

    endwin();
    return 0;
}
