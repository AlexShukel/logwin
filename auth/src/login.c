#include "app.h"
#include "auth.h"
#include "curses.h"
#include "utils.h"
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>

void login() {
    char masterPassword[PASSWORD_LENGTH];
    bool isValidLogin = false;

    if (!fileExists(USERS_DB)) {
        longjmp(exceptionJmpBuffer, NO_USERS_FOUND);
    }

    FILE *usersDB = fopen(USERS_DB, "rb");

    if (usersDB == NULL) {
        longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
    }

    uint64_t size = 0;
    fread(&size, sizeof(uint64_t), 1, usersDB);

    int currentLine = stdscr->_cury + 1;
    while (!isValidLogin) {
        mvprintw(currentLine, 0, "Enter your username:\n");
        clearLine(currentLine + 1, 0);
        inputString(loginData.name, USERNAME_LENGTH, false);

        mvprintw(currentLine + 2, 0, "Enter your password:\n");
        inputString(masterPassword, PASSWORD_LENGTH, true);

        for (uint64_t i = 0; i < size; ++i) {
            User user;
            fread(&user, sizeof(User), 1, usersDB);

            uint8_t hash[SIZE_OF_SHA_256_HASH];
            calc_sha_256(hash, masterPassword, strlen(masterPassword));

            if (strcmp(user.name, loginData.name) == 0 &&
                are_hashes_equal(user.hash, hash)) {
                isValidLogin = true;
                break;
            }
        }

        fseek(usersDB, sizeof(uint64_t), SEEK_SET);

        if (!isValidLogin) {
            mvprintErrorMessage(
                currentLine - 1, 0,
                "Username or password is invalid. Please, try again.\n");
        }
    }

    nullifyString(masterPassword, PASSWORD_LENGTH);
    memcpy(loginData.key, masterPassword, PASSWORD_LENGTH);

    erase();
    fclose(usersDB);
}