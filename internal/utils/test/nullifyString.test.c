#include "gclados.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

// Should nullify the rest of the string
TEST(nullify_stirng_1) {
    char *str = malloc(50);
    strcpy(str, "test");
    nullifyString(str, 50);

    int i = 0;
    char initialStr[] = "test";
    while (initialStr[i] != '\0') {
        ensure(str[i], gclados.toEqualChar(initialStr[i]));
        ++i;
    }

    for (i = i + 1; i < 50; ++i) {
        ensure(str[i], gclados.toEqualUnsignedChar(0));
    }

    free(str);
}
