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

void printLogin(Login login, int firstLine, bool visible) {
    mvprintw(firstLine + 0, 0, "Url: %s\n", login.url);
    mvprintw(firstLine + 1, 0, "Username: %s\n",
             visible ? login.username : "...");
    mvprintw(firstLine + 2, 0, "Password: %s\n",
             visible ? login.password : "...");
}

void printLogins(const Login *logins, int size, int selected, int firstLine,
                 bool *visible) {
    for (int i = 0; i < size; ++i) {
        if (selected == i) {
            attron(COLOR_PAIR(GREEN_TEXT_COLOR));
        }
        printLogin(logins[i], firstLine + i * 4, visible[i]);
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

            printw("- Use arrow keys to select a login.\n");
            printw("- Press enter to modify login.\n");
            printw("- Press space to make login data visible.\n");
            printw("- Press 'v' to make all logins visible.\n");
            printw("- Press ESC to go back.\n\n");
            printColorText(GREEN_TEXT_COLOR, "In total %d entries:\n", size);

            enableKeypad();

            int firstLine = stdscr->_cury;
            int selected = 0;
            bool hasSelected = true;
            bool areAllVisible = false;
            bool visible[size];
            for (int i = 0; i < size; ++i) {
                visible[i] = false;
            }

            printLogins(logins, size, 0, firstLine, visible);

            while (1) {
                int ch = getch();

                if (ERR == ch) {
                    continue;
                }

                if (ESC_KEY == ch) {
                    hasSelected = false;
                    break;
                }

                if (SPACE_KEY == ch) {
                    visible[selected] = visible[selected] ? false : true;
                }

                if ('v' == ch) {
                    areAllVisible = areAllVisible ? false : true;
                    for (int i = 0; i < size; ++i) {
                        visible[i] = areAllVisible;
                    }
                }

                selected = handleSelectedChange(ch, selected, size);

                if ('\n' == ch) {
                    break;
                };

                printLogins(logins, size, selected, firstLine, visible);
            }

            if (hasSelected) {
                handleLoginSelect(logins[selected], selected);
            }

            disableKeypad();
        }
    }

    logwinMain();
}
