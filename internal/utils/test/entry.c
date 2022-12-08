#include "gclados.h"
#include <stdbool.h>
extern GcladosTest __gcladosTest_file_exists_1(char *description);
extern GcladosTest __gcladosTest_file_exists_2(char *description);
extern GcladosTest __gcladosTest_contains_specified_char_1(char *description);
extern GcladosTest __gcladosTest_contains_specified_char_2(char *description);
extern GcladosTest __gcladosTest_contains_special_char_1(char *description);
extern GcladosTest __gcladosTest_contains_special_char_2(char *description);
extern GcladosTest __gcladosTest_is_strong_password_1(char *description);
extern GcladosTest __gcladosTest_is_strong_password_2(char *description);
extern GcladosTest __gcladosTest_nullify_stirng_1(char *description);

int main() {
    gcladosColors.setColorsSupported(true);
    gcladosSetUpdateSnapshots(false);
    GcladosTest gcladosTests0[] = {
        __gcladosTest_file_exists_1("Should return false if file does not exists"),
        __gcladosTest_file_exists_2("Should return true if file exists"),
    };
    GcladosTestSuite gcladosTestSuite0 = gcladosCreateTestSuite("/cygdrive/c/Git/logwin/internal/utils/test/fileExists.test.c", gcladosTests0, 2);
    GcladosTest gcladosTests1[] = {
        __gcladosTest_contains_specified_char_1("Should return true if password contains specified char"),
        __gcladosTest_contains_specified_char_2("Should return false if password does not contain specified char"),
        __gcladosTest_contains_special_char_1("Should return true if password contains special char"),
        __gcladosTest_contains_special_char_2("Should return false if password does not contain special char"),
        __gcladosTest_is_strong_password_1("Should return empty bit-flag for strong password"),
        __gcladosTest_is_strong_password_2("Should return non empty bit-flag for weak password"),
    };
    GcladosTestSuite gcladosTestSuite1 = gcladosCreateTestSuite("/cygdrive/c/Git/logwin/internal/utils/test/isStrongPassword.test.c", gcladosTests1, 6);
    GcladosTest gcladosTests2[] = {
        __gcladosTest_nullify_stirng_1("Should nullify the rest of the string"),
    };
    GcladosTestSuite gcladosTestSuite2 = gcladosCreateTestSuite("/cygdrive/c/Git/logwin/internal/utils/test/nullifyString.test.c", gcladosTests2, 1);
    GcladosTestSuite gcladosTestSuites[] = {
        gcladosTestSuite0,
        gcladosTestSuite1,
        gcladosTestSuite2,
    };
    return gcladosRunTestSuites(gcladosTestSuites, 3);
}
