#include "curses.h"
#include "main.h"
#include "utils.h"
#include <stdbool.h>

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

    AES_init_ctx_iv(&loginCredentials.aesContext, loginData.key, loginData.iv);
    AES_CBC_encrypt_buffer(&loginCredentials.aesContext, password,
                           PASSWORD_LENGTH);

    memcpy(loginCredentials.cipher, password, PASSWORD_LENGTH);

    saveLoginCredentials(&loginCredentials);
    logwinMain();
}
