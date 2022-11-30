#include "curses.h"
#include "main.h"
#include "menu.h"

void logwinMain() {
    erase();
    printw("Welcome to main logwin interface!\n");

    // Main interface options
    char addLoginCredentialsOption[] = "Add login credentials";
    char listLoginCredentialsOption[] = "List all my login credentials";

    char *options[] = {addLoginCredentialsOption, listLoginCredentialsOption};

    int answer = showMenu("Choose one from the following actions:", options,
                          sizeof(options) / sizeof(char *), "");

    if (answer == ADD_NEW) {
        // Add login credentials
        addLoginCredentials();
    } else if (answer == LIST_ALL) {
        // List all credentials
        listAllCredentials();
    }

    return;
}
