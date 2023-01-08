#include "app.h"
#include "errorHandler.h"
#include <stdio.h>

void printExitCodeMessage(int exitCode) {
    switch (exitCode) {
    case MANUAL_EXIT: {
        printf("App closed. Log out successfully!\n");
        break;
    }

    case TERMINAL_DOES_NOT_SUPPORT_COLOR: {
        fprintf(stderr, "Your terminal does not support color\n");
        break;
    }

    case SYSTEM_ERROR: {
        perror("");
        break;
    }

    case NO_USERS_FOUND: {
        fprintf(stderr,
                "No users found in the database. Please, create an account.");
        break;
    }

    case USER_NOT_FOUND: {
        fprintf(stderr, "User specified in file name was not found.");
        break;
    }

    default:
        break;
    }
}
