#include "filterLogins.c"
#include "gclados.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void ensureStringEquality(char *str1, char *str2) {
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        ensure(str1[i], gclados.toEqualChar(str2[i]));
        ++i;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        ensure(0, gclados.toEqualInt(1));
    }
}

// Should filter logins by username and url
TEST(filter_logins_1) {
    Login login1 = {.username = "bca", .url = "qqqq", .password = "1"};

    Login login2 = {.username = "Venom", .url = "test", .password = "2"};

    Login login3 = {.username = "bcb", .url = "bc", .password = "3"};

    Login logins[] = {login1, login2, login3};
    int size = sizeof(logins) / sizeof(Login);

    FilteredLogins filteredLogins = filterLogins(logins, size, "bc");

    ensure(filteredLogins.size, gclados.toEqualInt(2));

    if (filteredLogins.logins != NULL) {
        ensure(filteredLogins.logins[0].password[0], gclados.toEqualChar('1'));
        ensure(filteredLogins.logins[1].password[0], gclados.toEqualChar('3'));

        free(filteredLogins.logins);
    }
}

// Should not filter logins if filter is empty
TEST(filter_logins_2) {
    Login login1 = {.username = "bca", .url = "qqqq", .password = "1"};
    Login login2 = {.username = "Venom", .url = "test", .password = "2"};
    Login login3 = {.username = "bcb", .url = "bc", .password = "3"};

    Login logins[] = {login1, login2, login3};
    int size = sizeof(logins) / sizeof(Login);

    FilteredLogins filteredLogins = filterLogins(logins, size, "");

    ensure(filteredLogins.size, gclados.toEqualInt(3));

    if (filteredLogins.logins != NULL) {
        ensure(filteredLogins.logins[0].password[0], gclados.toEqualChar('1'));
        ensure(filteredLogins.logins[1].password[0], gclados.toEqualChar('2'));
        ensure(filteredLogins.logins[2].password[0], gclados.toEqualChar('3'));

        free(filteredLogins.logins);
    }
}

// Should find not case sensitive substring
TEST(strcasestr_1) {
    ensureStringEquality(strcasestr("Hello", "he"), "Hello");
    ensureStringEquality(strcasestr("Hello WoRLd", "world"), "WoRLd");
}
