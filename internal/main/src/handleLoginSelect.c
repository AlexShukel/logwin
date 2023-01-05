#include "app.h"
#include "curses.h"
#include "main.h"
#include "menu.h"
#include "utils.h"
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

enum ActionWithLogin { DELETE, MODIFY, COPY, GO_BACK };

void deleteLogin(int index) {
    char filename[USERNAME_LENGTH + 4];
    getUserDataFilename(filename);

    FILE *userDataDB = fopen(filename, "r+b");

    if (userDataDB == NULL) {
        longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
    }

    int size;
    fread(&size, sizeof(int), 1, userDataDB);

    fseek(userDataDB, sizeof(struct AES_ctx) + (index + 1) * sizeof(Login),
          SEEK_CUR);
    int restLoginsSize = size - index - 1;
    Login restLogins[restLoginsSize];
    fread(restLogins, sizeof(Login), restLoginsSize, userDataDB);

    fseek(userDataDB,
          sizeof(int) + sizeof(struct AES_ctx) + index * sizeof(Login),
          SEEK_SET);
    fwrite(restLogins, sizeof(Login), restLoginsSize, userDataDB);

    rewind(userDataDB);
    --size;
    fwrite(&size, sizeof(int), 1, userDataDB);

    fclose(userDataDB);
}

void modifyLogin(Login login, int index) {
    erase();

    printw("Modify url:\n");
    modifyString(login.url, URL_LENGTH);

    printw("Modify username:\n");
    modifyString(login.username, USERNAME_LENGTH);

    printw("Modify password:\n");
    modifyString(login.password, PASSWORD_LENGTH);

    saveLoginCredentials(&login, index);
}

void handleLoginSelect(Login login, int index) {
    erase();

    printLogin(login, stdscr->_cury, true);
    ++stdscr->_cury;

    char deleteOption[] = "Delete login";
    char modifyOption[] = "Modify login";
    char copyOption[] = "Copy password to clipboard";
    char returnBackOption[] = "Go back to list";
    char *options[] = {deleteOption, modifyOption, copyOption,
                       returnBackOption};

    int answer = showMenu("Possible actions with login:", options,
                          sizeof(options) / sizeof(char *),
                          "Please, select one of the following actions.");

    switch (answer) {
    case DELETE: {
        deleteLogin(index);
        break;
    }

    case MODIFY: {
        modifyLogin(login, index);
        break;
    }

    case COPY: {
        PDC_setclipboard(login.password, strlen(login.password));
        break;
    }

    case GO_BACK: {
        break;
    }

    default: {
        break;
    }
    }

    listLogins();
}
