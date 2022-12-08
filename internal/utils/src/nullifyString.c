#include "utils.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>


void nullifyString(char *password, size_t capacity) {
    assert(password != NULL);

    size_t length = strlen(password);

    for (int i = length + 1; i < capacity; ++i) {
        password[i] = 0;
    }
}
