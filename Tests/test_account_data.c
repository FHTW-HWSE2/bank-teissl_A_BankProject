#include "unity/unity.h"
#include "src/data/account_data.h"

#define TEST_CSV "test_accounts_data.csv"

void setUp(void) {
    FILE *file = fopen(TEST_CSV, "w");
    fputs("FirstName,LastName,SSN,Address,phone,email,BranchCode,Balance,AccountNumber\n", file);
    fputs("Ana,Jovic,1234567890,Ulica 5,0612345678,ana@mail.com,B1,5000,11112222\n", file);
    fclose(file);
}



void tearDown(void) {
    remove(TEST_CSV);
    remove("temp.csv");
}

void test_save_and_account_exists(void) {
    BankAccount acc = {
        .first_name = "Ana",
        .last_name = "Jovic",
        .ssn = "1234567890",
        .address = "Ulica 5",
        .phone = "0612345678",
        .email = "ana@mail.com",
        .branch_code = "B1",
        .balance = 5000,
        .account_number = "11112222"
    };

    TEST_ASSERT_EQUAL_INT(0, save_account_to_csv(TEST_CSV, &acc));
    TEST_ASSERT_TRUE(account_exists(TEST_CSV, "11112222"));
    TEST_ASSERT_FALSE(account_exists(TEST_CSV, "99999999"));
}

void test_get_account_by_number(void) {
    BankAccount acc = {
        .first_name = "Ana",
        .last_name = "Jovic",
        .ssn = "1234567890",
        .address = "Ulica 5",
        .phone = "0612345678",
        .email = "ana@mail.com",
        .branch_code = "B1",
        .balance = 5000,
        .account_number = "11112222"
    };

    save_account_to_csv(TEST_CSV, &acc);

    BankAccount loaded;
    TEST_ASSERT_EQUAL_INT(0, get_account_by_account_number("11112222", &loaded));
    TEST_ASSERT_EQUAL_STRING(acc.first_name, loaded.first_name);
    TEST_ASSERT_EQUAL_STRING(acc.account_number, loaded.account_number);
    TEST_ASSERT_EQUAL_UINT64(acc.balance, loaded.balance);
}

void test_remove_account(void) {
    BankAccount acc = {
        .first_name = "Ana",
        .last_name = "Jovic",
        .ssn = "1234567890",
        .address = "Ulica 5",
        .phone = "0612345678",
        .email = "ana@mail.com",
        .branch_code = "B1",
        .balance = 5000,
        .account_number = "11112222"
    };

    save_account_to_csv(TEST_CSV, &acc);
    TEST_ASSERT_TRUE(account_exists(TEST_CSV, "11112222"));

    TEST_ASSERT_EQUAL_INT(0, remove_account(&acc));
    TEST_ASSERT_FALSE(account_exists(TEST_CSV, "11112222"));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_save_and_account_exists);
    RUN_TEST(test_get_account_by_number);
    RUN_TEST(test_remove_account);
    return UNITY_END();
}
