#ifndef MENU_H
#define MENU_H

#include <stddef.h>

int handleSelectedChange(int key, int currentSelected, int size);

int showMenu(char *menuTitle, char **menuOptions, size_t menuSize,
             char *inputMessage);

#endif
