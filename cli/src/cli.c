#include "auth.h"
#include "constants.h"
#include "curses.h"
#include "menu.h"
#include "sha256.h"
#include "utils.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

void initConsole() {
    initscr();

    if (has_colors() == FALSE) {
        endwin();
        fprintf(stderr, "Your terminal does not support color\n");
        exit(1);
    }

    start_color();
    init_pair(ERROR_TEXT_COLOR, COLOR_RED, COLOR_BLACK);
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

    switch (answer) {

    case LOGIN: {
        login();
        break;
    }

    case SIGN_UP: {
        signUp();
        break;
    }

    // TODO: delete this code
    default: {
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
        break;
    }
    }

    endwin();
    return 0;
}
