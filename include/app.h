#ifndef APP_H
#define APP_H

#define USERNAME_LENGTH 255
#define PASSWORD_LENGTH 255
#define USERS_DB "usersDB.bin"

#include "sha256.h"

enum UserAction { LOGIN, SIGN_UP };

typedef struct {
    char name[USERNAME_LENGTH];
    uint8_t hash[SIZE_OF_SHA_256_HASH];
} User;

#endif
