#include "aes.h"
#include "curses.h"
#include "main.h"
#include "utils.h"
#include <stdbool.h>
#include <stdint.h>

void encryptPassword(struct AES_ctx *aesContext, uint8_t *buffer) {
    AES_init_ctx_iv(aesContext, loginData.key, loginData.iv);
    AES_CBC_encrypt_buffer(aesContext, buffer, PASSWORD_LENGTH);
}

void addNewLogin() {
    Login loginCredentials;

    printw("Input website url:\n");
    inputString(loginCredentials.url, URL_LENGTH, false);

    printw("Input username:\n");
    inputString(loginCredentials.username, USERNAME_LENGTH, false);

    char password[PASSWORD_LENGTH];
    printw("Input password:\n");
    inputString(password, PASSWORD_LENGTH, true);

    nullifyString(password, PASSWORD_LENGTH);

    encryptPassword(&loginCredentials.aesContext, password);

    memcpy(loginCredentials.cipher, password, PASSWORD_LENGTH);

    saveLoginCredentials(&loginCredentials, -1);
    logwinMain();
}
