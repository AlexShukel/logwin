#include "app.h"
#include "curses.h"
#include "main.h"
#include "menu.h"
#include "utils.h"
#include <errno.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>

void decryptPassword(Login *credentials) {
    AES_init_ctx_iv(&credentials->aesContext, loginData.key, loginData.iv);
    AES_CBC_decrypt_buffer(&credentials->aesContext, credentials->cipher,
                           PASSWORD_LENGTH);
}

void printLogins(const Login *logins, int size, int selected, int firstLine) {
    for (int i = 0; i < size; ++i) {
        if (selected == i) {
            attron(COLOR_PAIR(GREEN_TEXT_COLOR));
        }
        mvprintw(firstLine + i * 4 + 0, 0, "Url: %s\n", logins[i].url);
        mvprintw(firstLine + i * 4 + 1, 0, "Username: %s\n",
                 logins[i].username);
        mvprintw(firstLine + i * 4 + 2, 0, "Password: %s\n", logins[i].cipher);
        if (selected == i) {
            attroff(COLOR_PAIR(GREEN_TEXT_COLOR));
        }
        mvprintw(firstLine + i * 4 + 3, 0, "--------\n");
    }
}

void listLogins() {
    char filename[USERNAME_LENGTH + 4];
    getUserDataFilename(filename);

    FILE *userDataDB = fopen(filename, "rb");

    if (userDataDB == NULL) {
        if (fileExists(filename)) {
            longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
        } else {
            printErrorMessage("You haven't saved any credentials. Please, go "
                              "back.\n");

            // TODO: extract this logic
            printw("Press ESC key to go back...\n");

            noecho();
            while (1) {
                char ch = getch();

                if (ch == ERR) {
                    continue;
                }

                if (ch == ESC_KEY) {
                    break;
                }
            }
            echo();
        }
    } else {
        int size = 0;
        fread(&size, sizeof(int), 1, userDataDB);

        Login logins[size];
        fread(logins, sizeof(Login), size, userDataDB);

        for (int i = 0; i < size; ++i) {
            decryptPassword(&logins[i]);
        }

        fclose(userDataDB);

        printw("Use arrow keys and press enter to select a login. Press ESC to "
               "go back.\n");
        printColorText(GREEN_TEXT_COLOR, "In total %d entries:\n", size);

        int firstLine = stdscr->_cury;
        printLogins(logins, size, 0, firstLine);

        enableKeypad();
        int selected = 0;

        while (1) {
            int ch = getch();

            if (ERR == ch) {
                continue;
            }

            if (ESC_KEY == ch) {
                break;
            }

            selected = handleSelectedChange(ch, selected, size);

            if ('\n' == ch) {
                break;
            };

            printLogins(logins, size, selected, firstLine);
        }

        disableKeypad();
    }

    logwinMain();
}
