#include "app.h"
#include "auth.h"
#include "curses.h"
#include "sha256.h"
#include "utils.h"
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>

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
    char newUsername[USERNAME_LENGTH];
    bool isValidUsername = false;
    int currentLine = stdscr->_cury + 1;

    bool isFileExists = fileExists(USERS_DB);

    FILE *usersDB = fopen(USERS_DB, isFileExists ? "r+b" : "wb");

    if (usersDB == NULL) {
        longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
    }

    int size = 0;

    if (isFileExists) {
        fread(&size, sizeof(int), 1, usersDB);
    } else {
        fwrite(&size, sizeof(int), 1, usersDB);
    }

    User users[size];

    fread(users, sizeof(User), size, usersDB);

    // Input username
    while (!isValidUsername) {
        mvprintw(currentLine, 0, "New username:\n");
        clearLine(currentLine + 1, 0);
        inputString(newUsername, USERNAME_LENGTH, false);

        bool usernameExists = false;
        for (int i = 0; i < size; ++i) {
            if (strcmp(users[i].name, newUsername) == 0) {
                usernameExists = true;
                break;
            }
        }

        fseek(usersDB, sizeof(int), SEEK_SET);

        if (usernameExists) {
            mvprintErrorMessage(currentLine - 1, 0,
                                "This username already exists!");
        } else {
            isValidUsername = true;
        }
    }

    bool arePasswordsSame = false;
    char newPassword[PASSWORD_LENGTH];
    char repeatedNewPassword[PASSWORD_LENGTH];

    currentLine = stdscr->_cury + 1;

    uint8_t bitFlag = 0;

    // Input master password
    do {
        mvprintw(currentLine, 0, "New master password:\n");
        inputString(newPassword, PASSWORD_LENGTH, true);

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
        inputString(repeatedNewPassword, PASSWORD_LENGTH, true);

        if (strcmp(newPassword, repeatedNewPassword) == 0) {
            arePasswordsSame = true;
        } else {
            mvprintErrorMessage(currentLine - 1, 0,
                                "Master password does not match with repeated "
                                "password. Try again.\n");
        }
    }

    // Write new user to db
    uint8_t hash[SIZE_OF_SHA_256_HASH];
    calc_sha_256(hash, newPassword, strlen(newPassword));

    User user;

    memcpy(user.name, newUsername, USERNAME_LENGTH);
    memcpy(user.hash, hash, SIZE_OF_SHA_256_HASH);

    fseek(usersDB, 0, SEEK_END);
    fwrite(&user, sizeof(User), 1, usersDB);
    rewind(usersDB);
    ++size;
    fwrite(&size, sizeof(int), 1, usersDB);

    fclose(usersDB);

    erase();
}