#include "gclados.h"
#include <stdbool.h>
extern GcladosTest __gcladosTest_sha256_1(char *description);

int main() {
    gcladosColors.setColorsSupported(true);
    gcladosSetUpdateSnapshots(false);
    GcladosTest gcladosTests0[] = {
        __gcladosTest_sha256_1("Should return string"),
    };
    GcladosTestSuite gcladosTestSuite0 = gcladosCreateTestSuite("/cygdrive/c/Git/logwin/sha256/test/sha256.test.c", gcladosTests0, 1);
    GcladosTestSuite gcladosTestSuites[] = {
        gcladosTestSuite0,
    };
    return gcladosRunTestSuites(gcladosTestSuites, 1);
}
