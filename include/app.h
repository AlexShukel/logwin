#ifndef APP_H
#define APP_H

#include "./aes/aes.h"
#include <setjmp.h>

#define USERNAME_LENGTH 32
#define PASSWORD_LENGTH 32
#define URL_LENGTH 128
#define USERS_DB "usersDB.bin"

#define DEFAULT_TEXT_COLOR 0
#define ERROR_TEXT_COLOR 1
#define GREEN_TEXT_COLOR 2

#define ESC_KEY 27

#define HASH_LEN 32
#define SALT_LEN 16

enum AuthUserAction { LOGIN, SIGN_UP };

enum ErrorCode {
    IGNORE,
    MANUAL_EXIT,
    TERMINAL_DOES_NOT_SUPPORT_COLOR,
    SYSTEM_ERROR,
    NO_USERS_FOUND,
};

typedef struct {
    char name[USERNAME_LENGTH];
    uint8_t hash[HASH_LEN];
    uint8_t salt[SALT_LEN];
    uint8_t iv[AES_BLOCKLEN];
} User;

typedef struct {
    char name[USERNAME_LENGTH];
    uint8_t key[PASSWORD_LENGTH];
    uint8_t iv[AES_BLOCKLEN];
} LoginData;

// Variables for argon2 algorithm
extern uint32_t t_cost;
extern uint32_t m_cost;
extern uint32_t parallelism;

extern LoginData loginData;
extern jmp_buf exceptionJmpBuffer;

#endif
