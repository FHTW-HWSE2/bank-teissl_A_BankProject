#include "unity.h"

#include "../mocks/Mockcreate_account.h"
#include "../mocks/Mockuser_interface.h"
#include "create_account.h"


void setUp(void) {}
void tearDown(void) {}

void test_create_account_logic_should_fill_and_save_account(void)
{
    BankAccount dummy_account;
    memset(&dummy_account, 0, sizeof(BankAccount));
    strcpy(dummy_account.account_number, "12345678");

    // Mocks
    generate_unique_account_number_ExpectAndReturn("12345678");
    start_account_creation_ui_Expect(&dummy_account);
    save_account_to_csv_Expect("../assets/accounts.csv", &dummy_account);

    // Run actual function
    create_account_logic();
}