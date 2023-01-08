#include "filterLogins.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *strcasestr(const char *str, const char *substr) {
    const char *p1 = str;
    const char *p2 = substr;
    const char *returnValue = *p2 == 0 ? str : 0;

    while (*p1 != 0 && *p2 != 0) {
        if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2)) {
            if (returnValue == 0) {
                returnValue = p1;
            }

            p2++;
        } else {
            p2 = substr;
            if (returnValue != 0) {
                p1 = returnValue + 1;
            }

            if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2)) {
                returnValue = p1;
                p2++;
            } else {
                returnValue = 0;
            }
        }

        p1++;
    }

    return *p2 == 0 ? (char *)returnValue : 0;
}

FilteredLogins filterLogins(Login *logins, int size, char *filter) {
    if (filter == NULL || filter[0] == '\0') {
        FilteredLogins filteredLogin;

        filteredLogin.size = size;
        filteredLogin.logins = malloc(sizeof(Login) * size);

        memcpy(filteredLogin.logins, logins, size * sizeof(Login));

        return filteredLogin;
    }

    bool matchesFilter[size];

    for (int i = 0; i < size; ++i) {
        matchesFilter[i] = true;
    }

    FilteredLogins filteredLogins = {.size = size, .logins = NULL};

    for (int i = 0; i < size; ++i) {
        Login login = logins[i];

        char *foundUsername = strcasestr(login.username, filter);
        char *foundUrl = strcasestr(login.url, filter);

        if (foundUsername == NULL && foundUrl == NULL) {
            matchesFilter[i] = false;
            --filteredLogins.size;
        }
    }

    filteredLogins.logins = malloc(filteredLogins.size * sizeof(Login));

    int i = 0;
    for (int j = 0; j < size; ++j) {
        if (matchesFilter[j]) {
            filteredLogins.logins[i] = logins[j];
            ++i;
        }
    }

    return filteredLogins;
}
