#include "aes.h"
#include "gclados.h"
#include "main/main.h"
#include "utils/utils.h"
#include <stdint.h>
#include <stdio.h>

#define SIZE 32

// TODO use asserts here
// Should get encrypted plaintext from double transformation
TEST(basic_usage) {
    struct AES_ctx ctx;

    uint8_t key[] = "master password";
    uint8_t iv[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    char str[SIZE] = "Some sample plain text";
    nullifyString(str, SIZE);

    FILE *logFile = fopen("log.txt", "w");

    fprintf(logFile, "\n raw buffer \n");
    fprintf(logFile, "%s", str);

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, str, SIZE);

    fprintf(logFile, "\n Encrypted buffer\n");

    for (int i = 0; i < SIZE; ++i) {
        fprintf(logFile, "%.2x", str[i]);
    }

    // Save context and cipher in a file
    FILE *file = fopen("temp.bin", "wb");

    if (file != NULL) {
        fwrite(&ctx, sizeof(struct AES_ctx), 1, file);
        fwrite(str, SIZE, 1, file);
        fclose(file);
    }

    file = fopen("temp.bin", "rb");

    if (file != NULL) {
        fprintf(logFile, "\n Decrypted buffer\n");

        struct AES_ctx newCtx;
        fread(&newCtx, sizeof(struct AES_ctx), 1, file);
        char newStr[SIZE];
        fread(newStr, SIZE, 1, file);

        AES_init_ctx_iv(&newCtx, key, iv);
        AES_CBC_decrypt_buffer(&newCtx, newStr, SIZE);

        fprintf(logFile, "%s", newStr);

        fprintf(logFile, "\n");

        fclose(file);
    }

    remove("temp.bin");
}
