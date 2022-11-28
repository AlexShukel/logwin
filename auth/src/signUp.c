#include "auth.h"
#include "constants.h"
#include "curses.h"
#include "sha256.h"
#include "utils.h"
#include <stdbool.h>

bool signUp() {
    char newUsername[USERNAME_LENGTH];
    bool isValidUsername = false;
    int currentLine = stdscr->_cury + 1;

    bool isFileExists = fileExists(USERS_DB);

    FILE *usersDB = fopen(USERS_DB, isFileExists ? "r+b" : "w");

    u_int64_t size = 0;

    if (!isFileExists) {
        fwrite(&size, sizeof(u_int64_t), 1, usersDB);
    } else {
        fread(&size, sizeof(u_int64_t), 1, usersDB);
    }

    // Input username
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
            printErrorMessage(currentLine - 1, 0,
                              "Master password does not match with repeated "
                              "password. Try again.\n");
        }
    }

    // Write new user to db
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
        fprintf(stderr, "Error: unable to open users DB file.\n");
        return false;
    }

    erase();
    echo();
    return true;
}