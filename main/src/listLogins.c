#include "curses.h"
#include "main.h"
#include "utils.h"
#include <errno.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>

void decryptPassword(Login *credentials) {
    AES_init_ctx_iv(&credentials->aesContext, loginData.key, loginData.iv);
    AES_CBC_decrypt_buffer(&credentials->aesContext, credentials->cipher,
                           PASSWORD_LENGTH);
}

void listLogins() {
    char filename[USERNAME_LENGTH + 4];
    getUserDataFilename(filename);

    FILE *userDataDB = fopen(filename, "rb");

    if (userDataDB == NULL) {
        if (fileExists(filename)) {
            longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
        } else {
            printErrorMessage("You haven't saved any credentials. Please, go "
                              "back.\n");
        }
    } else {
        uint64_t size = 0;
        fread(&size, sizeof(uint64_t), 1, userDataDB);

        printColorText(GREEN_TEXT_COLOR, "In total %d entries:\n", size);

        for (uint64_t i = 0; i < size; ++i) {
            Login credentials;
            fread(&credentials, sizeof(Login), 1, userDataDB);
            decryptPassword(&credentials);

            printw("Url: %s\n", credentials.url);
            printw("Username: %s\n", credentials.username);
            printw("Password: %s\n", credentials.cipher);
            printw("--------\n");
        }

        fclose(userDataDB);
    }

    printw("Press any key to go back...\n");

    while (1) {
        char ch = getch();

        if (ch == ERR) {
            continue;
        }

        break;
    }

    logwinMain();
}
