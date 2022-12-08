#include "../src/isStrongPassword.c"
#include "gclados.h"
#include <stdbool.h>

int isCharacterA(int c) { return c == 'a'; }

// Should return true if password contains specified char
TEST(contains_specified_char_1) {
    char password[] = "car";

    ensure(containsSpecifiedChar(password, isCharacterA), gclados.toBeTruthy());
}

// Should return false if password does not contain specified char
TEST(contains_specified_char_2) {
    char password[] = "hello four world!";

    ensure(containsSpecifiedChar(password, isCharacterA), gclados.toBeFalsy());
}

// Should return true if password contains special char
TEST(contains_special_char_1) {
    ensure(containsSpecialChar("hello$world"), gclados.toBeTruthy());
    ensure(containsSpecialChar("(a!%$#bB*&^)"), gclados.toBeTruthy());
}

// Should return false if password does not contain special char
TEST(contains_special_char_2) {
    ensure(containsSpecialChar("hello world..."), gclados.toBeFalsy());
    ensure(containsSpecialChar(".,/\\//a\a//';"), gclados.toBeFalsy());
}

// Should return empty bit-flag for strong password
TEST(is_strong_password_1) {
    ensure(isStrongPassword("Alex@123aaaa"), gclados.toEqualUnsignedChar(0));
    ensure(isStrongPassword("jZx*(cv)&9l%AI@"), gclados.toEqualUnsignedChar(0));
}

// Should return non empty bit-flag for weak password
TEST(is_strong_password_2) {
    ensure(isStrongPassword("Aa1$"), gclados.toEqualUnsignedChar(0b00000001));

    ensure(isStrongPassword("Aa$aaaaaaaaa"),
           gclados.toEqualUnsignedChar(0b00000010));

    ensure(isStrongPassword("A1#AAAAAAAAA"),
           gclados.toEqualUnsignedChar(0b00000100));

    ensure(isStrongPassword("a1#aaaaaaaaa"),
           gclados.toEqualUnsignedChar(0b00001000));

    ensure(isStrongPassword("a1Aaaaaaaaaa"),
           gclados.toEqualUnsignedChar(0b00010000));
}
