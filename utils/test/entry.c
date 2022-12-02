#include "gclados.h"
#include <stdbool.h>
extern GcladosTest __gcladosTest_file_exists_1(char *description);
extern GcladosTest __gcladosTest_file_exists_2(char *description);
extern GcladosTest __gcladosTest_nullify_stirng_1(char *description);

int main() {
    gcladosColors.setColorsSupported(true);
    gcladosSetUpdateSnapshots(false);
    GcladosTest gcladosTests0[] = {
        __gcladosTest_file_exists_1("Should return false if file does not exists"),
        __gcladosTest_file_exists_2("Should return true if file exists"),
    };
    GcladosTestSuite gcladosTestSuite0 = gcladosCreateTestSuite("/cygdrive/c/Git/logwin/utils/test/fileExists.test.c", gcladosTests0, 2);
    GcladosTest gcladosTests1[] = {
        __gcladosTest_nullify_stirng_1("Should nullify the rest of the string"),
    };
    GcladosTestSuite gcladosTestSuite1 = gcladosCreateTestSuite("/cygdrive/c/Git/logwin/utils/test/nullifyString.test.c", gcladosTests1, 1);
    GcladosTestSuite gcladosTestSuites[] = {
        gcladosTestSuite0,
        gcladosTestSuite1,
    };
    return gcladosRunTestSuites(gcladosTestSuites, 2);
}
