#include "gclados.h"
#include <stdbool.h>
extern GcladosTest __gcladosTest_file_exists_1(char *description);
extern GcladosTest __gcladosTest_file_exists_2(char *description);

int main() {
    gcladosColors.setColorsSupported(true);
    gcladosSetUpdateSnapshots(false);
    GcladosTest gcladosTests0[] = {
        __gcladosTest_file_exists_1("Should return false if file does not exists"),
        __gcladosTest_file_exists_2("Should return true if file exists"),
    };
    GcladosTestSuite gcladosTestSuite0 = gcladosCreateTestSuite("/cygdrive/c/Git/logwin/utils/test/fileExists.test.c", gcladosTests0, 2);
    GcladosTestSuite gcladosTestSuites[] = {
        gcladosTestSuite0,
    };
    return gcladosRunTestSuites(gcladosTestSuites, 1);
}
