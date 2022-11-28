#include "gclados.h"
#include "sha256.h"

// Should return true if hashes are the same
TEST(sha256_hashes_comparison_1) {
    char hash1[SIZE_OF_SHA_256_HASH];
    char hash2[SIZE_OF_SHA_256_HASH];

    calc_sha_256(hash1, "hello", 5);
    calc_sha_256(hash2, "hello", 5);

    ensure(are_hashes_equal(hash1, hash2), gclados.toEqualUnsignedChar(1));
}

// Should return false if hashes are not the same
TEST(sha256_hashes_comparison_2) {
    char hash1[SIZE_OF_SHA_256_HASH];
    char hash2[SIZE_OF_SHA_256_HASH];

    calc_sha_256(hash1, "help", 5);
    calc_sha_256(hash2, "hello", 5);

    ensure(are_hashes_equal(hash1, hash2), gclados.toEqualUnsignedChar(0));
}
