#include "app.h"
#include "auth.h"
#include "curses.h"
#include "utils.h"
#include <stdbool.h>
#include <stdint.h>

bool login() {
    bool isValidLogin = false;

    if (!fileExists(USERS_DB)) {
        fprintf(stderr,
                "No users found in the database. Please, create an account.");
        return false;
    }

    FILE *usersDB = fopen(USERS_DB, "rb");

    if (usersDB == NULL) {
        fprintf(stderr, "Error: unable to open users DB file.\n");
        return false;
    }

    uint64_t size = getElementsSize(usersDB);

    int currentLine = stdscr->_cury + 1;
    while (!isValidLogin) {
        mvprintw(currentLine, 0, "Enter your username:\n");
        clearLine(currentLine + 1, 0);
        inputString(loginData.name, USERNAME_LENGTH);

        noecho();
        mvprintw(currentLine + 2, 0, "Enter your password:\n");
        inputString(loginData.masterPassword, PASSWORD_LENGTH);
        echo();

        for (uint64_t i = 0; i < size; ++i) {
            User user;
            fread(&user, sizeof(User), 1, usersDB);

            uint8_t hash[SIZE_OF_SHA_256_HASH];
            calc_sha_256(hash, loginData.masterPassword,
                         strlen(loginData.masterPassword));

            if (strcmp(user.name, loginData.name) == 0 &&
                are_hashes_equal(user.hash, hash)) {
                isValidLogin = true;
                break;
            }
        }

        fseek(usersDB, sizeof(uint64_t), SEEK_SET);

        if (!isValidLogin) {
            printErrorMessage(
                currentLine - 1, 0,
                "Username or password is invalid. Please, try again.\n");
        }
    }

    erase();
    fclose(usersDB);
    return true;
}