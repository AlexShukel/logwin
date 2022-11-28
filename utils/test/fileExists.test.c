#include "gclados.h"
#include "utils.h"
#include <stdio.h>

// Should return false if file does not exists
TEST(file_exists_1) { ensure(fileExists("hello.txt"), gclados.toBeFalsy()); }

// Should return true if file exists
TEST(file_exists_2) {
    FILE *file = fopen("hello.txt", "w");

    if (file != NULL) {
        ensure(fileExists("hello.txt"), gclados.toBeTruthy());

        fclose(file);
        remove("hello.txt");
    }
}
