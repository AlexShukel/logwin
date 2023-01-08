#include "app.h"
#include "argon2.h"
#include "auth.h"
#include "curses.h"
#include "usersDB.h"
#include "utils.h"
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void login() {
    char masterPassword[PASSWORD_LEN];
    bool isValidLogin = false;
    int userIndex = -1;

    if (!fileExists(USERS_DB)) {
        longjmp(exceptionJmpBuffer, NO_USERS_FOUND);
    }

    int size;
    User *users = NULL;

    if (readAllUsers(&users, &size)) {
        longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
    }

    int currentLine = stdscr->_cury + 1;
    while (!isValidLogin) {
        mvprintw(currentLine, 0, "Enter your username:\n");
        clearLine(currentLine + 1);
        inputString(loginData.name, USERNAME_LEN, false);

        mvprintw(currentLine + 2, 0, "Enter your password:\n");
        inputString(masterPassword, PASSWORD_LEN, true);

        nullifyString(masterPassword, PASSWORD_LEN);

        for (int i = 0; i < size; ++i) {
            if (strcmp(users[i].name, loginData.name) == 0) {
                uint8_t hash[HASH_LEN];
                argon2i_hash_raw(argon2_t_cost, argon2_m_cost,
                                 argon2_parallelism, masterPassword,
                                 PASSWORD_LEN, users[i].salt, SALT_LEN, hash,
                                 HASH_LEN);

                if (memcmp(users[i].hash, hash, HASH_LEN) == 0) {
                    isValidLogin = true;
                    userIndex = i;
                    break;
                }
            }
        }

        mvprintErrorMessage(
            currentLine - 1, 0,
            "Username or password is invalid. Please, try again.\n");
    }

    memcpy(loginData.key, masterPassword, PASSWORD_LEN);
    memcpy(loginData.iv, users[userIndex].iv, AES_BLOCKLEN);

    erase();
    free(users);
}