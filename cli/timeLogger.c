#include "timeLogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOG_FILE_NAME "time-log.txt"

time_t begin;

void logTime() {
    time_t end = time(NULL);

    int timeSpent = (int)difftime(end, begin);

    FILE *file = fopen(LOG_FILE_NAME, "a");

    if (file != NULL) {
        fprintf(file, "Program ended. User spent %d seconds.\n", timeSpent);

        fclose(file);
    }
}

void initTimer() {
    begin = time(NULL);
    FILE *file = fopen(LOG_FILE_NAME, "a");

    if (file != NULL) {
        fprintf(file, "Program started...\n");
        fclose(file);
    }

    atexit(logTime);
}
