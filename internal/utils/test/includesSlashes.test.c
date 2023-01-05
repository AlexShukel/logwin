#include "gclados.h"
#include "utils.h"

// Should return true if there are slashes in string
TEST(includes_slashes_1) {
    char str1[] = "/";
    char str2[] = "\\";
    char str3[] = "/a\\";

    ensure(includesSlashes(str1), gclados.toBeTruthy());
    ensure(includesSlashes(str2), gclados.toBeTruthy());
    ensure(includesSlashes(str3), gclados.toBeTruthy());
}

// Should return false if there are no slashes in string
TEST(includes_slashes_2) {
    char str[] = "a&u!)_-+*";

    ensure(includesSlashes(str), gclados.toBeFalsy());
}
