#ifndef MAIN_H
#define MAIN_H

#include "../aes/aes.h"
#include "../app.h"

enum MainInterfaceOptions { ADD_NEW, LIST_ALL };

typedef struct {
    char url[URL_LENGTH];
    char username[USERNAME_LENGTH];
    char cipher[PASSWORD_LENGTH];
    struct AES_ctx aesContext;
} Login;

void logwinMain();

void saveLoginCredentials(const Login *credentials);
void addNewLogin();

void listLogins();

// utils
void getUserDataFilename(char *filename);

#endif
