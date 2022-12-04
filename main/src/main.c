#include "app.h"
#include "curses.h"
#include "main.h"
#include "menu.h"
#include <setjmp.h>


enum MainInterfaceOptions { ADD_NEW, LIST_ALL, EXIT };

void logwinMain() {
    erase();
    printw("Welcome to main logwin interface!\n");

    // Main interface options
    char addNewLoginOption[] = "Add new login";
    char listAllLoginsOption[] = "List all logins";
    char exitOption[] = "Exit";

    char *options[] = {addNewLoginOption, listAllLoginsOption, exitOption};

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

    case EXIT: {
        longjmp(exceptionJmpBuffer, MANUAL_EXIT);
    }

    default:
        break;
    }

    return;
}
