#include <stdbool.h>

bool includesSlashes(const char *str) {
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '\\' || str[i] == '/') {
            return true;
        }

        ++i;
    }

    return false;
}
