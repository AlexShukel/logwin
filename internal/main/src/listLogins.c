#include "app.h"
#include "curses.h"
#include "main.h"
#include "menu.h"
#include "utils.h"
#include <errno.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void decryptLogin(struct AES_ctx *ctx, Login *credentials) {
    AES_init_ctx_iv(ctx, loginData.key, loginData.iv);
    AES_CBC_decrypt_buffer(ctx, (uint8_t *)credentials, sizeof(Login));
}

void printLogin(Login login, int firstLine) {
    mvprintw(firstLine + 0, 0, "Url: %s\n", login.url);
    mvprintw(firstLine + 1, 0, "Username: %s\n", login.username);
    mvprintw(firstLine + 2, 0, "Password: %s\n", login.password);
}

void printLogins(const Login *logins, int size, int selected, int firstLine) {
    for (int i = 0; i < size; ++i) {
        if (selected == i) {
            attron(COLOR_PAIR(GREEN_TEXT_COLOR));
        }
        printLogin(logins[i], firstLine + i * 4);
        if (selected == i) {
            attroff(COLOR_PAIR(GREEN_TEXT_COLOR));
        }
        mvprintw(firstLine + i * 4 + 3, 0, "--------\n");
    }
}

void noLoginsSaved() {
    printErrorMessage("You haven't saved any logins. Please, go "
                      "back.\n");

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

void listLogins() {
    erase();
    char filename[USERNAME_LENGTH + 4];
    getUserDataFilename(filename);

    FILE *userDataDB = fopen(filename, "rb");

    if (userDataDB == NULL) {
        if (fileExists(filename)) {
            longjmp(exceptionJmpBuffer, SYSTEM_ERROR);
        } else {
            noLoginsSaved();
        }
    } else {
        int size = 0;
        fread(&size, sizeof(int), 1, userDataDB);

        if (size == 0) {
            noLoginsSaved();

        } else {
            struct AES_ctx ctx;
            fread(&ctx, sizeof(struct AES_ctx), 1, userDataDB);

            Login logins[size];
            fread(logins, sizeof(Login), size, userDataDB);

            for (int i = 0; i < size; ++i) {
                decryptLogin(&ctx, logins + i);
            }

            fclose(userDataDB);

            printw("Use arrow keys and press enter to select a login. Press "
                   "ESC to "
                   "go back.\n");
            printColorText(GREEN_TEXT_COLOR, "In total %d entries:\n", size);

            int firstLine = stdscr->_cury;
            printLogins(logins, size, 0, firstLine);

            enableKeypad();
            int selected = 0;

            bool hasSelected = true;
            while (1) {
                int ch = getch();

                if (ERR == ch) {
                    continue;
                }

                if (ESC_KEY == ch) {
                    hasSelected = false;
                    break;
                }

                selected = handleSelectedChange(ch, selected, size);

                if ('\n' == ch) {
                    break;
                };

                printLogins(logins, size, selected, firstLine);
            }

            if (hasSelected) {
                handleLoginSelect(logins[selected], selected);
            }

            disableKeypad();
        }
    }

    logwinMain();
}
