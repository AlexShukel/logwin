#include "aes.h"
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

void encryptLogin(struct AES_ctx *ctx, Login *login) {
    AES_init_ctx_iv(ctx, loginData.key, loginData.iv);
    AES_CBC_encrypt_buffer(ctx, (uint8_t *)login, sizeof(Login));
}

// Passing negative index value, credentials will be appended to bottom of file.
void saveLoginCredentials(Login *credentials, int index) {
    char filename[USERNAME_LEN + USER_DATA_FILENAME_EXTENSION_LEN];
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

    struct AES_ctx ctx;
    fread(&ctx, sizeof(struct AES_ctx), 1, userDataDB);

    encryptLogin(&ctx, credentials);

    int metaDataOffset = sizeof(int) + sizeof(struct AES_ctx);

    fseek(userDataDB,
          metaDataOffset + getFileOffset(index, size) * sizeof(Login),
          SEEK_SET);

    fwrite(credentials, sizeof(Login), 1, userDataDB);

    fclose(userDataDB);
}
