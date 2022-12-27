#include "gclados.h"
#include <stdbool.h>
extern GcladosTest __gcladosTest_sha256_hashes_comparison_1(char *description);
extern GcladosTest __gcladosTest_sha256_hashes_comparison_2(char *description);

int main() {
    gcladosColors.setColorsSupported(true);
    gcladosSetUpdateSnapshots(false);
    GcladosTest gcladosTests0[] = {
        __gcladosTest_sha256_hashes_comparison_1("Should return true if hashes are the same"),
        __gcladosTest_sha256_hashes_comparison_2("Should return false if hashes are not the same"),
    };
    GcladosTestSuite gcladosTestSuite0 = gcladosCreateTestSuite("/cygdrive/c/Git/logwin/external/sha256/test/sha256.test.c", gcladosTests0, 2);
    GcladosTestSuite gcladosTestSuites[] = {
        gcladosTestSuite0,
    };
    return gcladosRunTestSuites(gcladosTestSuites, 1);
}
