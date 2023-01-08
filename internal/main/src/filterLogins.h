/**
 * @author Aleksandras Sukelovic <alex.shukel@gmail.com>
 * @version 1.0.0
 *
 * Module to filter logins.
 */

#ifndef FILTER_LOGINS_H
#define FILTER_LOGINS_H

#include "main.h"

typedef struct {
    int size;
    Login *logins;
} FilteredLogins;

// Function to filter logins.
FilteredLogins filterLogins(Login *logins, int size, char *filter);

#endif
