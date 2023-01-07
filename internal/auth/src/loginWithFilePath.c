#include "app.h"
#include "argon2.h"
#include "auth.h"
#include "curses.h"
#include "usersDB.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void getUsernameFromFilePath(const char *filePath, char *username) {
    int filePathLen = strlen(filePath);

    int lowerBound = filePathLen - USER_DATA_FILENAME_EXTENSION_LEN;
    int upperBound = lowerBound;

    while (filePath[lowerBound] != '\\') {
        --lowerBound;
    }

    for (int i = lowerBound + 1; i <= upperBound; ++i) {
        username[i - lowerBound - 1] = filePath[i];
    }

    username[upperBound + 1] = '\0';
}

bool userExists(const char *username, User *foundUser) {
    int size;
    User *users = NULL;

    if (readAllUsers(&users, &size)) {
        longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
    }

    bool userFound = false;
    for (int i = 0; i < size; ++i) {
        if (strcmp(users[i].name, username) == 0) {
            userFound = true;
            memcpy(foundUser, users + i, sizeof(User));
            break;
        }
    }

    free(users);
    return userFound;
}

void loginWithFilePath(const char *filePath) {
    char username[USERNAME_LENGTH];
    getUsernameFromFilePath(filePath, username);

    User user;

    if (!userExists(username, &user)) {
        longjmp(exceptionJmpBuffer, USER_NOT_FOUND);
    }

    printw("Your username is: %s\n", username);

    char password[PASSWORD_LENGTH];
    int currentLine = stdscr->_cury + 1;

    while (true) {
        mvprintw(currentLine, 0, "Please, enter your master password:\n");
        inputString(password, PASSWORD_LENGTH, true);

        nullifyString(password, PASSWORD_LENGTH);

        uint8_t hash[HASH_LEN];
        argon2i_hash_raw(t_cost, m_cost, parallelism, password, PASSWORD_LENGTH,
                         user.salt, SALT_LEN, hash, HASH_LEN);

        if (memcmp(hash, user.hash, HASH_LEN) == 0) {
            break;
        }

        mvprintErrorMessage(currentLine + 2, 0,
                            "Password is not correct. Please, try again.\n");
    }

    memcpy(loginData.key, password, PASSWORD_LENGTH);
    memcpy(loginData.iv, user.iv, AES_BLOCKLEN);
    memcpy(loginData.name, username, USERNAME_LENGTH);
}
