#include "curses.h"
#include "menu.h"
#include "sha256.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME_LENGTH 255
#define PASSWORD_LENGTH 255

typedef struct {
    char name[USERNAME_LENGTH];
    uint8_t hash[SIZE_OF_SHA_256_HASH];
} User;

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
    char printAllUsers[] = "Print all users";
    char *options[] = {loginOption, singUpOption, printAllUsers};
    int answer = showMenu("Authentication options:", options, 3,
                          "Login to existing account or create a new one.");

    echo();

    if (answer == 0) {
        // Login
        printw("Enter your username:\n");
    } else if (answer == 1) {
        // Sign up
        printw("New username:\n");
        char newUsername[USERNAME_LENGTH];
        inputString(newUsername);

        // Disable echo for password input
        noecho();
        bool arePasswordSame = false;
        char newPassword[PASSWORD_LENGTH];
        char repeatedNewPassword[PASSWORD_LENGTH];
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

        FILE *usersDB = fopen("usersDB.bin", "ab");

        if (usersDB != NULL) {
            uint8_t hash[SIZE_OF_SHA_256_HASH];
            calc_sha_256(hash, newPassword, strlen(newPassword));

            User user;

            memcpy(user.name, newUsername, USERNAME_LENGTH);
            memcpy(user.hash, hash, SIZE_OF_SHA_256_HASH);

            fwrite(&user, sizeof(User), 1, usersDB);

            fclose(usersDB);
        } else {
            fprintf(stderr, "Error: unable to open usersDB file.\n");
        }
    } else {
        FILE *usersDB = fopen("usersDB.bin", "rb");

        if (usersDB != NULL) {
            // TODO: store size of array in file
            while (!feof(usersDB)) {
                User user;

                fread(&user, sizeof(User), 1, usersDB);

                printf("%s\n", user.name);
                for (int i = 0; i < SIZE_OF_SHA_256_HASH; ++i) {
                    printf("%c", user.hash[i]);
                }
                printf("\n");
            }

            fclose(usersDB);
        } else {
            printf("Unable to open usersDB file\n");
        }
    }

    endwin();
    return 0;
}
