#include "app.h"
#include "auth.h"
#include "curses.h"
#include "menu.h"
#include "sha256.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    int answer = showMenu("Authentication options:", options, 3,
                          "Login to existing account or create a new one.");

    if (answer == LOGIN) {
        login();
    } else if (answer == SIGN_UP) {
        bool signedUp = signUp();
        if (signedUp) {
            printw("Signed up successfully!\nNow you can login to your "
                   "account.\n");
            login();
        };
    } else {
        FILE *usersDB = fopen(USERS_DB, "rb");

        if (usersDB != NULL) {
            u_int64_t size;
            fread(&size, sizeof(u_int64_t), 1, usersDB);

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
    }

    endwin();
    return 0;
}
