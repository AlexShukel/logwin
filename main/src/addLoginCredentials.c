#include "curses.h"
#include "main.h"
#include "utils.h"
#include <stdbool.h>

void addLoginCredentials() {
    LoginCredentials credentials;

    printw("Input username:\n");
    inputString(credentials.username, USERNAME_LENGTH);

    char password[PASSWORD_LENGTH];
    printw("Input password:\n");
    inputString(password, PASSWORD_LENGTH);

    nullifyString(password, PASSWORD_LENGTH);

    AES_init_ctx_iv(&credentials.aesContext, loginData.key, loginData.iv);
    AES_CBC_encrypt_buffer(&credentials.aesContext, password, PASSWORD_LENGTH);

    memcpy(credentials.cipher, password, PASSWORD_LENGTH);

    saveLoginCredentials(&credentials);
    logwinMain();
}
