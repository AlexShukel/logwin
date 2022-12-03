#ifndef APP_H
#define APP_H

#define USERNAME_LENGTH 32
#define PASSWORD_LENGTH 32
#define USERS_DB "usersDB.bin"

#define DEFAULT_TEXT_COLOR 0
#define ERROR_TEXT_COLOR 1
#define GREEN_TEXT_COLOR 2

#include "./aes/aes.h"
#include "./sha256/sha256.h"
#include <setjmp.h>

enum UserAction { LOGIN, SIGN_UP };

enum ErrorCode {
    IGNORE,
    SYSTEM_ERROR,
    NO_USERS_FOUND,
};

typedef struct {
    char name[USERNAME_LENGTH];
    uint8_t hash[SIZE_OF_SHA_256_HASH];
} User;

typedef struct {
    char name[USERNAME_LENGTH];
    uint8_t key[PASSWORD_LENGTH];
    uint8_t iv[AES_BLOCKLEN];
} LoginData;

extern LoginData loginData;
extern jmp_buf exceptionJmpBuffer;

#endif
