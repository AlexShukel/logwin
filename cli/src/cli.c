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

#define ERROR_TEXT_COLOR 1

enum UserAction {
    LOGIN,
    SIGN_UP,
};

typedef struct {
    char name[USERNAME_LENGTH];
    uint8_t hash[SIZE_OF_SHA_256_HASH];
} User;

static inline void clearLine(int y, int x) {
    mvdeleteln(y, x);
    mvinsertln(y, x);
}

void printErrorMessage(int y, int x, char *message) {
    attron(COLOR_PAIR(ERROR_TEXT_COLOR));
    mvprintw(y, x, message);
    attroff(COLOR_PAIR(ERROR_TEXT_COLOR));
}

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
        char username[USERNAME_LENGTH];
        char password[PASSWORD_LENGTH];
        bool isValidLogin = false;

        FILE *usersDB = fopen(USERS_DB, "rb");

        if (usersDB == NULL) {
            fprintf(
                stderr,
                "No users found in the database. Please, create an account.");
            return;
        }

        u_int64_t size;
        fread(&size, sizeof(u_int64_t), 1, usersDB);

        int currentLine = stdscr->_cury + 1;
        while (!isValidLogin) {
            mvprintw(currentLine, 0, "Enter your username:\n");
            clearLine(currentLine + 1, 0);
            inputString(username, USERNAME_LENGTH);

            noecho();
            mvprintw(currentLine + 2, 0, "Enter your password:\n");
            inputString(password, PASSWORD_LENGTH);
            echo();

            for (u_int64_t i = 0; i < size; ++i) {
                User user;
                fread(&user, sizeof(User), 1, usersDB);

                uint8_t hash[SIZE_OF_SHA_256_HASH];
                calc_sha_256(hash, password, strlen(password));

                if (strcmp(user.name, username) == 0 &&
                    are_hashes_equal(user.hash, hash)) {
                    isValidLogin = true;
                    break;
                }
            }

            fseek(usersDB, sizeof(u_int64_t), SEEK_SET);

            if (!isValidLogin) {
                printErrorMessage(
                    currentLine - 1, 0,
                    "Username or password is invalid. Please, try again.\n");
            }
        }

        fclose(usersDB);
        break;
    }

    case SIGN_UP: {
        char newUsername[USERNAME_LENGTH];
        bool isValidUsername = false;
        int currentLine = stdscr->_cury + 1;

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

        // input username
        while (!isValidUsername) {
            mvprintw(currentLine, 0, "New username:\n");
            clearLine(currentLine + 1, 0);
            inputString(newUsername, USERNAME_LENGTH);

            bool usernameExists = false;
            for (int i = 0; i < size; ++i) {
                User user;
                fread(&user, sizeof(User), 1, usersDB);
                if (strcmp(user.name, newUsername) == 0) {
                    usernameExists = true;
                    break;
                }
            }

            fseek(usersDB, sizeof(u_int64_t), SEEK_SET);

            if (usernameExists) {
                printErrorMessage(currentLine - 1, 0,
                                  "This username already exists!");
            } else {
                isValidUsername = true;
            }
        }

        // Disable echo for password input
        noecho();

        bool arePasswordsSame = false;
        char newPassword[PASSWORD_LENGTH];
        char repeatedNewPassword[PASSWORD_LENGTH];

        currentLine = stdscr->_cury + 1;

        while (!arePasswordsSame) {
            mvprintw(currentLine, 0, "New master password:\n");
            inputString(newPassword, PASSWORD_LENGTH);

            mvprintw(currentLine + 2, 0, "Repeat you master password:\n");
            inputString(repeatedNewPassword, PASSWORD_LENGTH);

            if (strcmp(newPassword, repeatedNewPassword) == 0) {
                arePasswordsSame = true;
            } else {
                printErrorMessage(
                    currentLine - 1, 0,
                    "Master password does not match with repeated "
                    "password. Try again.\n");
            }
        }

        if (usersDB != NULL) {
            uint8_t hash[SIZE_OF_SHA_256_HASH];
            calc_sha_256(hash, newPassword, strlen(newPassword));

            User user;

            memcpy(user.name, newUsername, USERNAME_LENGTH);
            memcpy(user.hash, hash, SIZE_OF_SHA_256_HASH);

            fseek(usersDB, 0, SEEK_END);
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
