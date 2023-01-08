/**
 * @author Aleksandras Sukelovic <alex.shukel@gmail.com>
 * @version 1.0.0
 *
 * Module to work with file containing all users. Provides functions to init,
 * read and write to this file.
 */

#ifndef USERS_DB_H
#define USERS_DB_H

#include "auth.h"

#define USERS_DB "usersDB.bin"

// Function to read all users from file. Outputs users and size to pointers
// provided in arguments. Returns 0 if success.
int readAllUsers(User **users, int *size);

// Function to save new user to the file. Returns 0 if success.
int saveNewUser(User *user);

// Function to read all users from file. If file was not found, initializes it.
// Outputs users and size to pointers provided in arguments. Returns 0 if
// success.
int readOrInitUsersDB(User **users, int *size);

#endif
