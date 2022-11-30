#ifndef APP_H
#define APP_H

#define USERNAME_LENGTH 32
#define PASSWORD_LENGTH 32
#define USERS_DB "usersDB.bin"

#define DEFAULT_TEXT_COLOR 0
#define ERROR_TEXT_COLOR 1
#define GREEN_TEXT_COLOR 2

#include "./sha256/sha256.h"

enum UserAction { LOGIN, SIGN_UP };

typedef struct {
    char name[USERNAME_LENGTH];
    uint8_t hash[SIZE_OF_SHA_256_HASH];
} User;

typedef struct {
    char name[USERNAME_LENGTH];
    char masterPassword[PASSWORD_LENGTH];
} LoginData;

extern LoginData loginData;

#endif
