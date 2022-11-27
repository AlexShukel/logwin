#include "curses.h"
#include "inputString.h"
#include "menu.h"
#include "sha256.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define USERNAME_LENGTH 255
#define PASSWORD_LENGTH 255

#define USERS_DB "usersDB.bin"

enum UserAction {
    LOGIN,
    SIGN_UP,
};

typedef struct {
    char name[USERNAME_LENGTH];
    uint8_t hash[SIZE_OF_SHA_256_HASH];
} User;

int main() {
    initscr();

    if (has_colors() == FALSE) {
        endwin();
        fprintf(stderr, "Your terminal does not support color\n");
        exit(1);
    }

    start_color();

    printw("Welcome to logwin!\n");

    // List of options
    char loginOption[] = "Login";
    char singUpOption[] = "Sign up";
    char printAllUsers[] = "Print all users";
    char *options[] = {loginOption, singUpOption, printAllUsers};

    // Get answer from menu
    int answer = showMenu("Authentication options:", options, 3,
                          "Login to existing account or create a new one.");

    echo();

    switch (answer) {

    case LOGIN: {
        printw("Enter your username:\n");
        break;
    }

    case SIGN_UP: {
        printw("New username:\n");
        char newUsername[USERNAME_LENGTH];
        inputString(newUsername, USERNAME_LENGTH);

        // Disable echo for password input
        noecho();
        init_pair(1, COLOR_RED, COLOR_BLACK);

        bool arePasswordsSame = false;
        char newPassword[PASSWORD_LENGTH];
        char repeatedNewPassword[PASSWORD_LENGTH];

        int currentLine = stdscr->_cury + 1;

        while (!arePasswordsSame) {
            mvprintw(currentLine, 0, "New master password:\n");
            inputString(newPassword, PASSWORD_LENGTH);

            mvprintw(currentLine + 2, 0, "Repeat you master password:\n");
            inputString(repeatedNewPassword, PASSWORD_LENGTH);

            if (strcmp(newPassword, repeatedNewPassword) == 0) {
                arePasswordsSame = true;
            } else {
                attron(COLOR_PAIR(1));
                mvprintw(currentLine - 1, 0,
                         "Master password does not match with repeated "
                         "password. Try again.\n");
                attroff(COLOR_PAIR(1));
            }
        }

        bool fileExists = false;
        if (access(USERS_DB, F_OK) == 0) {
            fileExists = true;
        }

        FILE *usersDB = fopen(USERS_DB, fileExists ? "r+b" : "w");

        u_int64_t size = 0;

        if (!fileExists) {
            fwrite(&size, sizeof(u_int64_t), 1, usersDB);
        } else {
            fread(&size, sizeof(u_int64_t), 1, usersDB);
        }

        if (usersDB != NULL) {
            uint8_t hash[SIZE_OF_SHA_256_HASH];
            calc_sha_256(hash, newPassword, strlen(newPassword));

            User user;

            memcpy(user.name, newUsername, USERNAME_LENGTH);
            memcpy(user.hash, hash, SIZE_OF_SHA_256_HASH);

            fwrite(&user, sizeof(User), 1, usersDB);
            rewind(usersDB);
            ++size;
            fwrite(&size, sizeof(u_int64_t), 1, usersDB);

            fclose(usersDB);
        } else {
            fprintf(stderr, "Error: unable to open usersDB file.\n");
        }
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
