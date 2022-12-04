#include "gclados.h"
#include <stdbool.h>
extern GcladosTest __gcladosTest_handle_selected_change_1(char *description);
extern GcladosTest __gcladosTest_handle_selected_change_2(char *description);
extern GcladosTest __gcladosTest_handle_selected_change_3(char *description);
extern GcladosTest __gcladosTest_handle_selected_change_4(char *description);

int main() {
    gcladosColors.setColorsSupported(true);
    gcladosSetUpdateSnapshots(false);
    GcladosTest gcladosTests0[] = {
        __gcladosTest_handle_selected_change_1("Should return size - 1 when selected item is 0 and KEY_UP pressed hello"),
        __gcladosTest_handle_selected_change_2("Should return 0 when selected item is size - 1 and KEY_DOWN pressed"),
        __gcladosTest_handle_selected_change_3("Should increase (on KEY_DOWN) selected item"),
        __gcladosTest_handle_selected_change_4("Should decrease (ont KEY_UP) selected item"),
    };
    GcladosTestSuite gcladosTestSuite0 = gcladosCreateTestSuite("./handleSelectedChange.test.c", gcladosTests0, 4);
    GcladosTestSuite gcladosTestSuites[] = {
        gcladosTestSuite0,
    };
    return gcladosRunTestSuites(gcladosTestSuites, 1);
}
