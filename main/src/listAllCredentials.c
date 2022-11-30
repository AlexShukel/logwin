#include "main.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>

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

    uint64_t size = getElementsSize(userDataDB);

    for (uint64_t i = 0; i < size; ++i) {
        LoginCredentials credentials;
        fread(&credentials, sizeof(LoginCredentials), 1, userDataDB);
        printf("Username: %s\n", credentials.username);
        printf("Password: %s\n", credentials.password);
        printf("----------------------------------------------------\n");
    }

    fclose(userDataDB);
}
