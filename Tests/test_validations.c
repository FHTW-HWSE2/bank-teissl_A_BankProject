#include "unity/unity.h"
#include "src/logic/validations.h"

// Wird vor jedem Test aufgerufen
void setUp(void) {}

// Wird nach jedem Test aufgerufen
void tearDown(void) {}

// ✅ Test für die Gültigkeit der Kontonummer (8 Ziffern)
void test_is_valid_account_number(void) {
    TEST_ASSERT_TRUE(is_valid_account_number("12345678"));
    TEST_ASSERT_FALSE(is_valid_account_number("1234567"));   // 7 Ziffern
    TEST_ASSERT_FALSE(is_valid_account_number("123456789")); // 9 Ziffern
    TEST_ASSERT_FALSE(is_valid_account_number("abcd5678"));  // enthält Buchstaben
}

// ✅ Test für die Gültigkeit der Sozialversicherungsnummer (10 Ziffern)
void test_is_valid_ssn(void) {
    TEST_ASSERT_TRUE(is_valid_ssn("1234567890"));
    TEST_ASSERT_FALSE(is_valid_ssn("12345"));      // zu kurz
    TEST_ASSERT_FALSE(is_valid_ssn("abcdefghij")); // nur Buchstaben
}

// ✅ Test für die Gültigkeit des Filialcodes (B1 oder b2 erlaubt)
void test_is_valid_branch_code(void) {
    TEST_ASSERT_TRUE(is_valid_branch_code("B1"));
    TEST_ASSERT_TRUE(is_valid_branch_code("b2"));
    TEST_ASSERT_FALSE(is_valid_branch_code("C3")); // ungültiger Code
    TEST_ASSERT_FALSE(is_valid_branch_code(""));   // leer
}

// ✅ Test für die Gültigkeit der Telefonnummer (nur Ziffern erlaubt)
void test_is_valid_phone_number(void) {
    TEST_ASSERT_TRUE(is_valid_phone_number("0123456789"));
    TEST_ASSERT_FALSE(is_valid_phone_number("123-456"));  // Bindestrich nicht erlaubt
    TEST_ASSERT_FALSE(is_valid_phone_number("(555)123")); // Klammern nicht erlaubt
    TEST_ASSERT_FALSE(is_valid_phone_number(""));         // leer
}

// ✅ Test für die Gültigkeit der E-Mail-Adresse
void test_is_valid_email(void) {
    TEST_ASSERT_TRUE(is_valid_email("user@example.com"));
    TEST_ASSERT_FALSE(is_valid_email("userexample.com"));   // kein @
    TEST_ASSERT_FALSE(is_valid_email("@example.com"));      // beginnt mit @
    TEST_ASSERT_FALSE(is_valid_email("user@.com"));         // . direkt nach @
    TEST_ASSERT_FALSE(is_valid_email("user@example."));     // endet mit .
    TEST_ASSERT_FALSE(is_valid_email(""));                  // leer
}

// Einstiegspunkt für Unity-Tests
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_is_valid_account_number);
    RUN_TEST(test_is_valid_ssn);
    RUN_TEST(test_is_valid_branch_code);
    RUN_TEST(test_is_valid_phone_number);
    RUN_TEST(test_is_valid_email);
    return UNITY_END();
}
