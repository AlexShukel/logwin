#include "aes.h"
#include "curses.h"
#include "main.h"
#include "utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

void addNewLogin() {
    Login loginCredentials;

    printw("Input website url:\n");
    inputString(loginCredentials.url, URL_LEN, false);

    printw("Input username:\n");
    inputString(loginCredentials.username, USERNAME_LEN, false);

    printw("Input password:\n");
    inputString(loginCredentials.password, PASSWORD_LEN, true);

    saveLoginCredentials(&loginCredentials, -1);
    logwinMain();
}
