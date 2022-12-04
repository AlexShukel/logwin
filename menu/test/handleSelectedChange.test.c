#include "curses.h"
#include "gclados.h"
#include "menu.h"

// Should return size - 1 when selected item is 0 and KEY_UP pressed hello
TEST(handle_selected_change_1) {
    ensure(handleSelectedChange(KEY_UP, 0, 5), gclados.toEqualInt(4));
}

// Should return 0 when selected item is size - 1 and KEY_DOWN pressed
TEST(handle_selected_change_2) {
    ensure(handleSelectedChange(KEY_DOWN, 4, 5), gclados.toEqualInt(0));
}

// Should increase (on KEY_DOWN) selected item
TEST(handle_selected_change_3) {
    ensure(handleSelectedChange(KEY_DOWN, 1, 5), gclados.toEqualInt(2));
}

// Should decrease (ont KEY_UP) selected item
TEST(handle_selected_change_4) {
    ensure(handleSelectedChange(KEY_UP, 4, 5), gclados.toEqualInt(3));
}
