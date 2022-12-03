#include "curses.h"
#include "main.h"
#include "menu.h"

void logwinMain() {
    erase();
    printw("Welcome to main logwin interface!\n");

    // Main interface options
    char addNewLoginOption[] = "Add login credentials";
    char listLoginCredentialsOption[] = "List all my login credentials";

    char *options[] = {addNewLoginOption, listLoginCredentialsOption};

    int answer = showMenu("Choose one from the following actions:", options,
                          sizeof(options) / sizeof(char *), "");

    if (answer == ADD_NEW) {
        // Add login credentials
        addNewLogin();
    } else if (answer == LIST_ALL) {
        // List all credentials
        listLogins();
    }

    return;
}
