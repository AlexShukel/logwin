#include "app.h"
#include "auth.h"
#include "curses.h"
#include "utils.h"
#include <stdbool.h>


void login() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    bool isValidLogin = false;

    if (!fileExists(USERS_DB)) {
        fprintf(stderr,
                "No users found in the database. Please, create an account.");
        return;
    }

    FILE *usersDB = fopen(USERS_DB, "rb");

    if (usersDB == NULL) {
        fprintf(stderr, "Error: unable to open users DB file.\n");
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
}