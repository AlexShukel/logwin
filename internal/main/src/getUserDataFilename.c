#include "app.h"
#include <string.h>

void getUserDataFilename(char *filename) {
    int i = 0;

    while (loginData.name[i] != '\0') {
        filename[i] = loginData.name[i];
        ++i;
    }

    memcpy(filename + i, ".bin\0", 5);
}