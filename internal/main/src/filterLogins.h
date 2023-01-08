#ifndef FILTER_LOGINS_H
#define FILTER_LOGINS_H

#include "main.h"

typedef struct {
    int size;
    Login *logins;
} FilteredLogins;

FilteredLogins filterLogins(Login *logins, int size, char *filter);

#endif
