#ifndef USERS_DB_H
#define USERS_DB_H

#include "auth.h"

#define USERS_DB "usersDB.bin"

int readAllUsers(User **users, int *size);

int saveNewUser(User *user);

int readOrInitUsersDB(User **users, int *size);

#endif
