#include "app.h"
#include "argon2.h"
#include "auth.h"
#include "curses.h"
#include "utils.h"
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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

    int size = 0;
    fread(&size, sizeof(int), 1, usersDB);

    User users[size];
    fread(users, sizeof(User), size, usersDB);

    int currentLine = stdscr->_cury + 1;
    while (!isValidLogin) {
        mvprintw(currentLine, 0, "Enter your username:\n");
        clearLine(currentLine + 1, 0);
        inputString(loginData.name, USERNAME_LENGTH, false);

        mvprintw(currentLine + 2, 0, "Enter your password:\n");
        inputString(masterPassword, PASSWORD_LENGTH, true);

        nullifyString(masterPassword, PASSWORD_LENGTH);

        uint8_t hash[HASH_LEN];
        argon2i_hash_raw(t_cost, m_cost, parallelism, masterPassword,
                         PASSWORD_LENGTH, salt, SALT_LEN, hash, HASH_LEN);

        for (int i = 0; i < size; ++i) {
            if (strcmp(users[i].name, loginData.name) == 0 &&
                memcmp(users[i].hash, hash, HASH_LEN) == 0) {
                isValidLogin = true;
                break;
            }
        }

        fseek(usersDB, sizeof(int), SEEK_SET);

        mvprintErrorMessage(
            currentLine - 1, 0,
            "Username or password is invalid. Please, try again.\n");
    }

    memcpy(loginData.key, masterPassword, PASSWORD_LENGTH);

    erase();
    fclose(usersDB);
}