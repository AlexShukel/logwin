/**
 * @author Aleksandras Sukelovic <alex.shukel@gmail.com>
 * @version 1.0.0
 *
 * Logwin app general definitions
 */

#ifndef APP_H
#define APP_H

#include "./aes/aes.h"
#include <setjmp.h>

// Lengths of stored variables
#define USERNAME_LEN 32
#define PASSWORD_LEN 32
#define URL_LEN 128

// Length of argon2 hash
#define HASH_LEN 32
// Length of salt used in argon2 hash algorithm
#define SALT_LEN 16
// Length of string ".logwin"
#define USER_DATA_FILENAME_EXTENSION_LEN 8

// Curses text colors
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
    char name[USERNAME_LEN];
    uint8_t key[PASSWORD_LEN];
    uint8_t iv[AES_BLOCKLEN];
} LoginData;

// Variables for argon2 algorithm
extern uint32_t argon2_t_cost;
extern uint32_t argon2_m_cost;
extern uint32_t argon2_parallelism;

extern LoginData loginData;
extern jmp_buf exceptionJmpBuffer;

#endif
