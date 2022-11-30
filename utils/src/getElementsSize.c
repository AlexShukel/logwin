#include "utils.h"
#include <stdio.h>

uint64_t getElementsSize(FILE *file) {
    uint64_t size = 0;

    fread(&size, sizeof(uint64_t), 1, file);

    return size;
}
