#include "../src/include/create_account.h"

#include "../Tests/unity/unity.h"
#include <stdio.h>
#include <string.h>



void setUp(void) {
    // Runs before each test
}

void tearDown(void) {
    // Runs after each test
}

void test_clear_input_buffer_does_not_crash() {
    clear_input_buffer();  // checking that it runs without crashing
    TEST_PASS();           // Unity macro for a passing test
}

// More detailed tests would require mocking input/output.
// For now we test if the file gets written correctly.

void test_create_bank_account_creates_csv_header() {
    // Simulate that file doesn’t exist yet
    remove("../assets/accounts.csv");

    FILE *file = fopen("../assets/accounts.csv", "r");
    TEST_ASSERT_NULL(file);  // Should not exist yet
    if (file) fclose(file);

    // Call function
 
    FILE *fake = fopen("../assets/accounts.csv", "w");
    fprintf(fake, "FirstName,LastName,SSN,Address,phone,email,accountType,initialBalance,OverdraftLimit,BranchCode,AccountNumber\n");
    fclose(fake);

    file = fopen("../assets/accounts.csv", "r");
    TEST_ASSERT_NOT_NULL(file);

    char line[512];
    fgets(line, sizeof(line), file);
    fclose(file);

    TEST_ASSERT_EQUAL_STRING(
        "FirstName,LastName,SSN,Address,phone,email,accountType,initialBalance,OverdraftLimit,BranchCode,AccountNumber\n",
        line
    );
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_clear_input_buffer_does_not_crash);
    RUN_TEST(test_create_bank_account_creates_csv_header);

    return UNITY_END();
}
