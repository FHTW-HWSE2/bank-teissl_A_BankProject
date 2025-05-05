#include "unity.h"
#include "Mockuser_interface.h"
#include "Mockaccount_data.h"
#include "create_account.h"

void setUp(void) {}
void tearDown(void) {}

void test_create_account_should_collect_input_and_save_account(void)
{
    // Simulate user input
    get_user_input_ExpectAndReturn("Enter first name: ", "John");
    get_user_input_ExpectAndReturn("Enter last name: ", "Doe");
    get_user_input_ExpectAndReturn("Enter SSN: ", "123456789");
    get_user_input_ExpectAndReturn("Enter address: ", "123 Main St");
    get_user_input_ExpectAndReturn("Enter phone: ", "555-1234");
    get_user_input_ExpectAndReturn("Enter email: ", "john@example.com");
    get_user_input_ExpectAndReturn("Enter branch code: ", "001");
    get_user_input_ExpectAndReturn("Enter account number: ", "98765432");

    // Expected account to be passed to save_account_to_csv
    BankAccount expected = {
        .first_name = "John",
        .last_name = "Doe",
        .ssn = "123456789",
        .address = "123 Main St",
        .phone = "555-1234",
        .email = "john@example.com",
        .branch_code = "001",
        .account_number = "98765432"
    };

    save_account_to_csv_Expect("accounts.csv", &expected);

    create_account();  // 🔁 The function under test
}
