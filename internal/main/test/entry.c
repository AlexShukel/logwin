#include "gclados.h"
#include <stdbool.h>
extern GcladosTest __gcladosTest_filter_logins_1(char *description);
extern GcladosTest __gcladosTest_filter_logins_2(char *description);
extern GcladosTest __gcladosTest_strcasestr_1(char *description);

int main() {
    gcladosColors.setColorsSupported(true);
    gcladosSetUpdateSnapshots(false);
    GcladosTest gcladosTests0[] = {
        __gcladosTest_filter_logins_1("Should filter logins by username and url"),
        __gcladosTest_filter_logins_2("Should not filter logins if filter is empty"),
        __gcladosTest_strcasestr_1("Should find not case sensitive substring"),
    };
    GcladosTestSuite gcladosTestSuite0 = gcladosCreateTestSuite("/cygdrive/c/Git/logwin/internal/main/test/filterLogins.test.c", gcladosTests0, 3);
    GcladosTestSuite gcladosTestSuites[] = {
        gcladosTestSuite0,
    };
    return gcladosRunTestSuites(gcladosTestSuites, 1);
}
