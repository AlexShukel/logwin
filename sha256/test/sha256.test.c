#include "gclados.h"
#include "sha256.h"
#include <stdio.h>

// Should return string
TEST(sha256_1) {
    char str[] = "Hello";
    printf("HELLO: %d\n", sizeof(str));
    // ensure(sha256(str), gclados.toEqualBytes(str, sizeof(str)));
}
