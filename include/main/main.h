#ifndef MAIN_H
#define MAIN_H

#include "../aes/aes.h"
#include "../app.h"

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
void printLogin(Login login, int firstLine);
void handleLoginSelect(Login login, int index);

// utils
void getUserDataFilename(char *filename);

#endif
