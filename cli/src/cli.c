#include "app.h"
#include "auth.h"
#include "curses.h"
#include "main.h"
#include "menu.h"
#include "sha256.h"
#include <errno.h>
#include <inttypes.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Global variables
LoginData loginData = {.iv = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                              0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f}};
jmp_buf exceptionJmpBuffer;

void initConsole() {
    initscr();

    if (has_colors() == FALSE) {
        longjmp(exceptionJmpBuffer, TERMINAL_DOES_NOT_SUPPORT_COLOR);
    }

    start_color();
    init_pair(DEFAULT_TEXT_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(ERROR_TEXT_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN_TEXT_COLOR, COLOR_GREEN, COLOR_BLACK);
}

int main() {
    // Errors handling
    int exitCode = setjmp(exceptionJmpBuffer);

    if (exitCode != IGNORE) {
        endwin();

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
            fprintf(
                stderr,
                "No users found in the database. Please, create an account.");
            break;
        }

        default:
            break;
        }

        return 0;
    }

    initConsole();
    printw("Welcome to logwin!\n");

    // List of options
    char loginOption[] = "Login";
    char singUpOption[] = "Sign up";
    char exitOption[] = "Exit";
    char *options[] = {loginOption, singUpOption, exitOption};

    // Get answer from menu
    int answer = showMenu("Authentication options:", options,
                          sizeof(options) / sizeof(char *),
                          "Login to existing account or create a new one.");

    if (answer == LOGIN) {
        login();
    } else if (answer == SIGN_UP) {
        signUp();
        printw("Signed up successfully!\nNow you can login to your "
               "account.\n");
        login();
    } else {
        longjmp(exceptionJmpBuffer, MANUAL_EXIT);
    }

    logwinMain();

    longjmp(exceptionJmpBuffer, MANUAL_EXIT);
}
