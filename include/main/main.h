#ifndef MAIN_H
#define MAIN_H

#include "../app.h"

enum MainInterfaceOptions { ADD_NEW, LIST_ALL };

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} LoginCredentials;

void logwinMain();

void saveLoginCredentials(const LoginCredentials *credentials);
void addLoginCredentials();

void listAllCredentials();

// utils
void getUserDataFilename(char *filename);

#endif
