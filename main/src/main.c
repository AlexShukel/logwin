#include "curses.h"
#include "main.h"
#include "menu.h"

void logwinMain() {
    erase();
    printw("Welcome to main logwin interface!\n");

    // Main interface options
    char addNewLoginOption[] = "Add new login";
    char listAllLoginsOption[] = "List all logins";

    char *options[] = {addNewLoginOption, listAllLoginsOption};

    int answer = showMenu("Choose one from the following actions:", options,
                          sizeof(options) / sizeof(char *), "");

    switch (answer) {
    case ADD_NEW: {
        addNewLogin();
        break;
    }

    case LIST_ALL: {
        listLogins();
        break;
    }

    default:
        break;
    }

    return;
}
