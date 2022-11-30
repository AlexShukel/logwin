#include "app.h"
#include "main.h"
#include "utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void saveLoginCredentials(const LoginCredentials *credentials) {
    char filename[USERNAME_LENGTH + 4];
    getUserDataFilename(filename);

    bool isFileExists = fileExists(filename);

    FILE *userDataDB = fopen(filename, isFileExists ? "r+b" : "wb");

    uint64_t size = 0;

    if (isFileExists) {
        size = getElementsSize(userDataDB);
    } else {
        fwrite(&size, sizeof(uint64_t), 1, userDataDB);
    }

    rewind(userDataDB);
    ++size;
    fwrite(&size, sizeof(uint64_t), 1, userDataDB);
    fseek(userDataDB, 0, SEEK_END);
    fwrite(credentials, sizeof(LoginCredentials), 1, userDataDB);

    fclose(userDataDB);
}
