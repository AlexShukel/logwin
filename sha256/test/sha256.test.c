#include "gclados.h"
#include "sha256.h"
#include <stdio.h>

struct string_vector {
    const char *input;
    const char *output;
};

static const struct string_vector STRING_VECTORS[] = {
    {"", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"},
    {"abc", "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"},
    {"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef",
     "a8ae6e6ee929abea3afcfc5258c8ccd6f85273e0d4626d26c7279f3250f77c8e"},
    {"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcde",
     "057ee79ece0b9a849552ab8d3c335fe9a5f1c46ef5f1d9b190c295728628299c"},
    {"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0",
     "2a6ad82f3620d3ebe9d678c812ae12312699d673240d5be8fac0910a70000d93"},
    {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
     "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1"},
    {"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno"
     "ijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
     "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1"}};

// SHA256 tests
TEST(sha256_1) {
    for (int i = 0; i < sizeof(STRING_VECTORS); ++i) {
        void *hash = malloc(SIZE_OF_SHA_256_HASH);
        calc_sha_256(hash, STRING_VECTORS[i].input,
                     strlen(STRING_VECTORS[i].input));
        ensure((void *)STRING_VECTORS[i].output,
               gclados.toEqualBytes(hash, SIZE_OF_SHA_256_HASH));
        free(hash);
    }
}
