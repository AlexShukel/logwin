#include <sha256.h>
#include <stdio.h>
#include <string.h>

int main() {
    uint8_t hash[SIZE_OF_SHA_256_HASH];
    char input[] = "Hello world!";
    calc_sha_256(hash, input, strlen(input));

    printf("Hash of %s is: %s", input, hash);

    return 0;
}
