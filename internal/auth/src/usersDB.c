#include "auth.h"
#include "usersDB.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int readAllUsers(User **users, int *size) {
    FILE *file = fopen(USERS_DB, "rb");

    if (file == NULL) {
        return 1;
    }

    fread(size, sizeof(int), 1, file);

    *users = (User *)malloc(*size * sizeof(User));

    if (*users == NULL) {
        return 1;
    }

    fread(*users, sizeof(User), *size, file);

    fclose(file);
    return 0;
}

int saveNewUser(User *user) {
    FILE *file = fopen(USERS_DB, "r+b");

    if (file == NULL) {
        return 1;
    }

    int size;
    fread(&size, sizeof(int), 1, file);

    ++size;
    fseek(file, 0, SEEK_SET);
    fwrite(&size, sizeof(int), 1, file);

    fseek(file, 0, SEEK_END);
    fwrite(user, sizeof(User), 1, file);

    fclose(file);
    return 0;
}

int readOrInitUsersDB(User **users, int *size) {
    if (fileExists(USERS_DB)) {
        return readAllUsers(users, size);
    }

    FILE *file = fopen(USERS_DB, "wb");

    if (file == NULL) {
        return 1;
    }

    *size = 0;
    fwrite(size, sizeof(int), 1, file);

    fclose(file);
}
