
#include "unity/unity.h"
#include "./mocks/Mockaccount_data.h"

#define TEST_CSV "test_accounts_data.csv"

void setUp(void) {
    Mockaccount_data_Init();
}

void tearDown(void) {
    Mockaccount_data_Verify();
    Mockaccount_data_Destroy();
}

void test_unique_generation_uses_account_exists(void) {
    const char* dummy_file = "test_accounts_data.csv";
    const char* dummy_acc_num = "1234567890";

    account_exists_ExpectAndReturn(dummy_file, dummy_acc_num, false);

    bool exists = account_exists(dummy_file, dummy_acc_num);

    TEST_ASSERT_FALSE(exists);
}


void test_get_account_by_number(void) {
    const char* dummy_file = "test_accounts_data.csv";
    const char* dummy_acc_num = "1234567890";
    BankAccount acc;

    get_account_by_account_number_ExpectAndReturn(dummy_file, dummy_acc_num, &acc, 0);

    int result = get_account_by_account_number(dummy_file, dummy_acc_num, &acc);

    TEST_ASSERT_EQUAL_INT(0, result);
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

    save_account_to_csv_ExpectAndReturn(TEST_CSV, &acc, 0);
    account_exists_ExpectAndReturn(TEST_CSV, "11112222", true);
    account_exists_ExpectAndReturn(TEST_CSV, "99999999", false);

    TEST_ASSERT_EQUAL_INT(0, save_account_to_csv(TEST_CSV, &acc));
    TEST_ASSERT_TRUE(account_exists(TEST_CSV, "11112222"));
    TEST_ASSERT_FALSE(account_exists(TEST_CSV, "99999999"));
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

    save_account_to_csv_ExpectAndReturn(TEST_CSV, &acc, 0);
    account_exists_ExpectAndReturn(TEST_CSV, "11112222", true);
    remove_account_ExpectAndReturn(TEST_CSV, &acc, 0);
    account_exists_ExpectAndReturn(TEST_CSV, "11112222", false);

    TEST_ASSERT_EQUAL_INT(0, save_account_to_csv(TEST_CSV, &acc));
    TEST_ASSERT_TRUE(account_exists(TEST_CSV, "11112222"));
    TEST_ASSERT_EQUAL_INT(0, remove_account(TEST_CSV, &acc));
    TEST_ASSERT_FALSE(account_exists(TEST_CSV, "11112222"));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_save_and_account_exists);
    RUN_TEST(test_get_account_by_number);
    RUN_TEST(test_remove_account);
    RUN_TEST(test_unique_generation_uses_account_exists);
    return UNITY_END();
}
