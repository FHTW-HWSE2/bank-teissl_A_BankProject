#include "unity.h"

#include "Mockaccount_data.h"
#include "Mockuser_interface.h"
#include "create_account.h"

void setUp(void) {}
void tearDown(void) {}

void test_create_account_should_save_valid_account(void) {
    BankAccount account;

    char fake_name[] = "Alice";
    double fake_balance = 100.0;
    char fake_account_number[] = "12345678";

    // Expectation for get_nonempty_input() – 3 arguments
    get_nonempty_input_Expect("Enter full name: ", fake_name, 100);
    
    // Expectation for balance (returns double)
    get_valid_balance_ExpectAndReturn("Enter initial balance: ", fake_balance, fake_balance);

    // Expectation for account number generation
    generate_unique_account_number_ExpectAndReturn(fake_account_number);

    // Save function call
    save_account_to_csv_Expect("assets/accounts.csv", &account);

    // Final message
    print_message_Expect("Account created successfully.");

    // Call function under test
    create_bank_account();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_account_should_save_valid_account);
    return UNITY_END();
}
