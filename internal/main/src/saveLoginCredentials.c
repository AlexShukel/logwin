#include "app.h"
#include "main.h"
#include "utils.h"
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int getFileOffset(int index, int size) {
    if (index < 0 || index >= size) {
        return size - 1;
    }

    return index;
}

void saveLoginCredentials(const Login *credentials, int index) {
    char filename[USERNAME_LENGTH + 4];
    getUserDataFilename(filename);

    bool isFileExists = fileExists(filename);

    FILE *userDataDB = fopen(filename, isFileExists ? "r+b" : "wb");

    if (userDataDB == NULL) {
        longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
    }

    int size = 0;

    if (isFileExists) {
        fread(&size, sizeof(int), 1, userDataDB);
    } else {
        fwrite(&size, sizeof(int), 1, userDataDB);
    }

    if (index < 0) {
        rewind(userDataDB);
        ++size;
        fwrite(&size, sizeof(int), 1, userDataDB);
    }

    fseek(userDataDB, sizeof(int) + getFileOffset(index, size) * sizeof(Login),
          SEEK_SET);
    fwrite(credentials, sizeof(Login), 1, userDataDB);

    fclose(userDataDB);
}
