#ifndef APP_H
#define APP_H

#include "./aes/aes.h"
#include <setjmp.h>

#define USERNAME_LENGTH 32
#define PASSWORD_LENGTH 32
#define URL_LENGTH 128
#define HASH_LEN 32
#define SALT_LEN 16
#define USER_DATA_FILENAME_EXTENSION_LEN 8

// curses text colors
#define DEFAULT_TEXT_COLOR 0
#define ERROR_TEXT_COLOR 1
#define GREEN_TEXT_COLOR 2

// Keyboard keys
#define ESC_KEY 27
#define SPACE_KEY 32

enum AuthUserAction { LOGIN, SIGN_UP };

enum ErrorCode {
    IGNORE,
    MANUAL_EXIT,
    TERMINAL_DOES_NOT_SUPPORT_COLOR,
    SYSTEM_ERROR,
    NO_USERS_FOUND,
    USER_NOT_FOUND
};

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
