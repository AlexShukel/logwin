#ifndef AUTH_UTILS_H
#define AUTH_UTILS_H

#include "app.h"

void generateSalt(uint8_t salt[SALT_LEN]);

void generateIv(uint8_t iv[AES_BLOCKLEN]);

#endif
