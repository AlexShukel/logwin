#include "app.h"
#include "authUtils.h"
#include <stdlib.h>

void generateSalt(uint8_t salt[SALT_LEN]) {
    for (int i = 0; i < SALT_LEN; ++i) {
        salt[i] = rand() % 255;
    }
}

void generateIv(uint8_t iv[AES_BLOCKLEN]) {
    for (int i = 0; i < AES_BLOCKLEN; ++i) {
        iv[i] = rand() % 255;
    }
}