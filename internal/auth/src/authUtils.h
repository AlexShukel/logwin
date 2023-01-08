/**
 * @author Aleksandras Sukelovic <alex.shukel@gmail.com>
 * @version 1.0.0
 *
 * Auth utils.
 */

#ifndef AUTH_UTILS_H
#define AUTH_UTILS_H

#include "app.h"

// Generates random salt to given salt pointer.
void generateSalt(uint8_t salt[SALT_LEN]);

// Generates random initialization vector ot given iv pointer.
void generateIv(uint8_t iv[AES_BLOCKLEN]);

#endif
