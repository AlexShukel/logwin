#ifndef MAIN_H
#define MAIN_H

#include "../aes/aes.h"
#include "../app.h"

enum MainInterfaceOptions { ADD_NEW, LIST_ALL };

typedef struct {
    char username[USERNAME_LENGTH];
    char cipher[PASSWORD_LENGTH];
    struct AES_ctx aesContext;
} LoginCredentials;

void logwinMain();

void saveLoginCredentials(const LoginCredentials *credentials);
void addLoginCredentials();

void listAllCredentials();

// utils
void getUserDataFilename(char *filename);

#endif
