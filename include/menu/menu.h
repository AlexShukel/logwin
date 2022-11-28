#ifndef MENU_H
#define MENU_H

#include <stddef.h>

int showMenu(char *menuTitle, char **menuOptions, size_t menuSize,
             char *inputMessage);

#endif
