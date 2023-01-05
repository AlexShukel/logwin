#include "app.h"
#include "auth.h"
#include "curses.h"
#include "main.h"
#include "menu.h"
#include <errno.h>
#include <inttypes.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Global variables
uint32_t t_cost = 2;
uint32_t m_cost = (1 << 16);
uint32_t parallelism = 1;

LoginData loginData;
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

    srand(time(NULL));

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
