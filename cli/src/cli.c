#include "app.h"
#include "auth.h"
#include "curses.h"
#include "main.h"
#include "menu.h"
#include "sha256.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LoginData loginData = {.iv = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                              0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f}};

void initConsole() {
    initscr();

    if (has_colors() == FALSE) {
        endwin();
        fprintf(stderr, "Your terminal does not support color\n");
        exit(1);
    }

    start_color();
    init_pair(DEFAULT_TEXT_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(ERROR_TEXT_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN_TEXT_COLOR, COLOR_GREEN, COLOR_BLACK);
}

int main() {
    initConsole();
    printw("Welcome to logwin!\n");

    // List of options
    char loginOption[] = "Login";
    char singUpOption[] = "Sign up";
    char printAllUsers[] = "Print all users";
    char *options[] = {loginOption, singUpOption, printAllUsers};

    // Get answer from menu
    int answer = showMenu("Authentication options:", options,
                          sizeof(options) / sizeof(char *),
                          "Login to existing account or create a new one.");

    if (answer == LOGIN) {
        if (!login()) {
            endwin();
            return 0;
        }
    } else if (answer == SIGN_UP) {
        bool signedUp = signUp();
        if (signedUp) {
            printw("Signed up successfully!\nNow you can login to your "
                   "account.\n");
            if (!login()) {
                endwin();
                return 0;
            }
        };
    } else if (answer == 2) {
        // TODO: delete test code
        FILE *usersDB = fopen(USERS_DB, "rb");

        if (usersDB != NULL) {
            uint64_t size;
            fread(&size, sizeof(uint64_t), 1, usersDB);

            for (int i = 0; i < size; ++i) {
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
    } else {
        endwin();
        return 0;
    }

    logwinMain();

    endwin();
    return 0;
}
