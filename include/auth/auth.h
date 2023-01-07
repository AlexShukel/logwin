#ifndef AUTH_H
#define AUTH_H

#include "../app.h"
#include <stdbool.h>

typedef struct {
    char name[USERNAME_LENGTH];
    uint8_t hash[HASH_LEN];
    uint8_t salt[SALT_LEN];
    uint8_t iv[AES_BLOCKLEN];
} User;

void login();
void signUp();

void loginWithFilePath(const char *filePath);

#endif
