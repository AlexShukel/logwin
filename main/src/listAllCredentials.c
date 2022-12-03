#include "main.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>

void decryptPassword(LoginCredentials *credentials) {
    AES_init_ctx_iv(&credentials->aesContext, loginData.key, loginData.iv);
    AES_CBC_decrypt_buffer(&credentials->aesContext, credentials->cipher,
                           PASSWORD_LENGTH);
}

void listAllCredentials() {
    char filename[USERNAME_LENGTH + 4];
    getUserDataFilename(filename);

    if (!fileExists(filename)) {
        // TODO: print error message
        return;
    }

    FILE *userDataDB = fopen(filename, "rb");

    if (userDataDB == NULL) {
        fprintf(stderr, "Error: unable to open %s file", filename);
        return;
    }

    uint64_t size = 0;
    fread(&size, sizeof(uint64_t), 1, userDataDB);

    // TODO: log into curses terminal
    for (uint64_t i = 0; i < size; ++i) {
        LoginCredentials credentials;
        fread(&credentials, sizeof(LoginCredentials), 1, userDataDB);
        printf("Username: %s\n", credentials.username);

        decryptPassword(&credentials);

        printf("%s\n", credentials.cipher);
        printf("\n");
        printf("----------------------------------------------------\n");
    }

    fclose(userDataDB);
}
