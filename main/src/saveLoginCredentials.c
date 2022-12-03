#include "app.h"
#include "main.h"
#include "utils.h"
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void saveLoginCredentials(const Login *credentials) {
    char filename[USERNAME_LENGTH + 4];
    getUserDataFilename(filename);

    bool isFileExists = fileExists(filename);

    FILE *userDataDB = fopen(filename, isFileExists ? "r+b" : "wb");

    if (userDataDB == NULL) {
        longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
    }

    uint64_t size = 0;

    if (isFileExists) {
        fread(&size, sizeof(uint64_t), 1, userDataDB);
    } else {
        fwrite(&size, sizeof(uint64_t), 1, userDataDB);
    }

    rewind(userDataDB);
    ++size;
    fwrite(&size, sizeof(uint64_t), 1, userDataDB);
    fseek(userDataDB, 0, SEEK_END);
    fwrite(credentials, sizeof(Login), 1, userDataDB);

    fclose(userDataDB);
}
