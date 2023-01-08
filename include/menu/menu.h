/**
 * @author Aleksandras Sukelovic <alex.shukel@gmail.com>
 * @version 1.0.0
 *
 * Menu module to select one option from the list using keyboard arrow keys.
 */

#ifndef MENU_H
#define MENU_H

#include <stddef.h>

// Function to increment or decrement currentSelected argument according to
// specified key (KEY_UP or KEY_DOWN). If another key is provided, returns the
// same currentSelected value.
int handleSelectedChange(int key, int currentSelected, int size);

// Function to show menu in console. Returns index of selected option.
int showMenu(char *menuTitle, char **menuOptions, size_t menuSize,
             char *inputMessage);

#endif
