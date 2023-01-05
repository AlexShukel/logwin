#include "app.h"
#include <string.h>

void getUserDataFilename(char *filename) {
    int i = 0;

    while (loginData.name[i] != '\0') {
        filename[i] = loginData.name[i];
        ++i;
    }

    memcpy(filename + i, ".logwin\0", USER_DATA_FILENAME_EXTENSION_LEN);
}