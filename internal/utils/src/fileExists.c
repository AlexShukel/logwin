#include "utils.h"
#include <stdbool.h>
#include <unistd.h>

bool fileExists(char *fileName) {
    if (access(fileName, F_OK) == 0) {
        return true;
    }

    return false;
};
