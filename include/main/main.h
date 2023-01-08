/**
 * @author Aleksandras Sukelovic <alex.shukel@gmail.com>
 * @version 1.0.0
 *
 * Main logwin module.
 */

#ifndef MAIN_H
#define MAIN_H

#include "../aes/aes.h"
#include "../app.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char url[URL_LEN];
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} Login;

// Function to print main logwin interface.
void logwinMain();

// Function to save login data in a file of authenticated user.
void saveLoginCredentials(Login *credentials, int index);

// Function to add new login from keyboard.
void addNewLogin();

// Function to print all logins with possibility to filter, modify, view or
// delete each record.
void listLogins();

// Function to print single login data.
void printLogin(Login login, int firstLine, bool visible);

// Function to print menu of possible actions with login: modify, delete or copy
// password to clipboard.
void handleLoginSelect(Login login, int index);

// Function to get filename of user data file. Outputs stirng to filename
// parameter in format "<username>.logwin"
void getUserDataFilename(char *filename);

#endif
