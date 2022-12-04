#include "curses.h"

int handleSelectedChange(int key, int currentSelected, int size) {
    if (KEY_UP == key) {
        if (currentSelected == 0) {
            currentSelected = size - 1;
        } else {
            --currentSelected;
        }
    }

    if (KEY_DOWN == key) {
        if (currentSelected == size - 1) {
            currentSelected = 0;
        } else {
            ++currentSelected;
        }
    }

    return currentSelected;
}