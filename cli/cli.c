/**
 * @author Aleksandras Sukelovic <alex.shukel@gmail.com>
 * @version 1.0.0
 *
 * Logwin cli entry point
 */

#include "app.h"
#include "auth.h"
#include "curses.h"
#include "errorHandler.h"
#include "main.h"
#include "menu.h"
#include "timeLogger.h"
#include "utils.h"
#include <errno.h>
#include <inttypes.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global variables
uint32_t argon2_t_cost = 2;
uint32_t argon2_m_cost = (1 << 16);
uint32_t argon2_parallelism = 1;

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

int main(int argc, char **argv) {
    // Initialization
    initConsole();
    srand(time(NULL));
    initTimer();

    // Errors handling
    int exitCode = setjmp(exceptionJmpBuffer);

    if (exitCode != IGNORE) {
        endwin();

        printExitCodeMessage(exitCode);

        return 0;
    }

    // Auth
    if (argc >= 2) {
        loginWithFilePath(argv[1]);
    } else {
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
    }

    // Main
    logwinMain();

    return 0;
}
