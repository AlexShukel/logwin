#include "app.h"
#include "argon2.h"
#include "auth.h"
#include "authUtils.h"
#include "curses.h"
#include "usersDB.h"
#include "utils.h"
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void erasePasswordStrengthCriteria(int firstLine) {
    for (int i = 0; i < NUMBER_OF_CRITERIA + 1; ++i) {
        mvdeleteln(firstLine, 0);
    }
}

void printPasswordStrengthCriterion(int y, uint8_t bitFlag, uint8_t criteria) {
    int color = bitFlag & criteria ? ERROR_TEXT_COLOR : GREEN_TEXT_COLOR;

    mvprintColorText(y, 0, color, "%s", strPasswordStrengthError(criteria));
}

void printPasswordStrengthCriteria(int firstLine, uint8_t bitFlag) {
    mvprintw(firstLine, 0, "Your password must meet following criteria:");

    for (int i = 0; i < NUMBER_OF_CRITERIA; ++i) {
        printPasswordStrengthCriterion(firstLine + i + 1, bitFlag,
                                       passwordStrengthCriteria[i]);
    }
}

void signUp() {
    char newUsername[USERNAME_LEN];
    bool isValidUsername = false;
    int currentLine = stdscr->_cury + 1;

    User *users = NULL;
    int size;

    if (readOrInitUsersDB(&users, &size)) {
        longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
    };

    // Input username
    while (!isValidUsername) {
        mvprintw(currentLine, 0, "New username:\n");
        clearLine(currentLine + 1);
        inputString(newUsername, USERNAME_LEN, false);

        bool containsSlashes = includesSlashes(newUsername);

        bool usernameExists = false;
        for (int i = 0; i < size; ++i) {
            if (strcmp(users[i].name, newUsername) == 0) {
                usernameExists = true;
                break;
            }
        }

        if (usernameExists) {
            mvprintErrorMessage(currentLine - 1, 0,
                                "This username already exists!");
        } else if (containsSlashes) {
            mvprintErrorMessage(currentLine - 1, 0,
                                "Username can not contain slashes!");
        } else {
            isValidUsername = true;
            clearLine(currentLine - 1);
            stdscr->_cury += 2;
        }
    }

    bool arePasswordsSame = false;
    char newPassword[PASSWORD_LEN];
    char repeatedNewPassword[PASSWORD_LEN];

    currentLine = stdscr->_cury + 1;

    uint8_t bitFlag = 0;

    // Input master password
    do {
        mvprintw(currentLine, 0, "New master password:\n");
        inputString(newPassword, PASSWORD_LEN, true);

        bitFlag = isStrongPassword(newPassword);

        if (bitFlag != 0) {
            printPasswordStrengthCriteria(currentLine + 2, bitFlag);
        } else {
            erasePasswordStrengthCriteria(currentLine + 2);
        }
    } while (bitFlag != 0);

    // Repeat master password
    while (!arePasswordsSame) {
        mvprintw(currentLine + 2, 0, "Repeat you master password:\n");
        inputString(repeatedNewPassword, PASSWORD_LEN, true);

        if (strcmp(newPassword, repeatedNewPassword) == 0) {
            arePasswordsSame = true;
        } else {
            mvprintErrorMessage(currentLine - 1, 0,
                                "Master password does not match with repeated "
                                "password. Try again.\n");
        }
    }

    User user;
    generateSalt(user.salt);
    generateIv(user.iv);

    uint8_t hash[HASH_LEN];
    nullifyString(newPassword, PASSWORD_LEN);
    argon2i_hash_raw(argon2_t_cost, argon2_m_cost, argon2_parallelism,
                     newPassword, PASSWORD_LEN, user.salt, SALT_LEN, hash,
                     HASH_LEN);

    memcpy(user.name, newUsername, USERNAME_LEN);
    memcpy(user.hash, hash, HASH_LEN);

    if (saveNewUser(&user)) {
        longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
    }

    free(users);
    erase();
}