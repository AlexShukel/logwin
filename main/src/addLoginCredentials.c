#include "curses.h"
#include "main.h"
#include "utils.h"
#include <stdbool.h>

void addLoginCredentials() {
    LoginCredentials credentials;

    printw("Input username:\n");
    inputString(credentials.username, USERNAME_LENGTH);
    printw("Input password:\n");
    inputString(credentials.password, PASSWORD_LENGTH);

    saveLoginCredentials(&credentials);
    logwinMain();
}
