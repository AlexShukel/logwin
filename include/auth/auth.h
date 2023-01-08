/**
 * @author Aleksandras Sukelovic <alex.shukel@gmail.com>
 * @version 1.0.0
 *
 * Auth logwin module.
 */

#ifndef AUTH_H
#define AUTH_H

#include "../app.h"
#include <stdbool.h>

typedef struct {
    char name[USERNAME_LEN];
    uint8_t hash[HASH_LEN];
    uint8_t salt[SALT_LEN];
    uint8_t iv[AES_BLOCKLEN];
} User;

// Function to print login ui.
void login();

// Function to print sign up ui.
void signUp();

// Function to login with specified filePath to user data file.
void loginWithFilePath(const char *filePath);

#endif
