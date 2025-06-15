cmake_minimum_required(VERSION 3.10)
project(BANK-Teissl_A_BANKPROJECT C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Coverage options
if(COVERAGE)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# Coverage report target
add_custom_target(coverage
    COMMAND gcovr --root .. --object-directory . --filter '../src/' --html --html-details -o coverage.html
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Global includes and compile options
include_directories(${PROJECT_SOURCE_DIR})
add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)

enable_testing()

# =======================
# Main Bank App executable
# =======================
add_executable(BankApp
    src/main.c
    src/presentation/user_interface.c
    src/presentation/report_ui.c
    src/data/account_data.c
    src/data/transactions_db.c
    src/data/report_data.c
    src/logic/controller.c
    src/logic/delete_account.c
    src/logic/create_account.c
    src/logic/update_account.c
    src/logic/bank_logic.c
    src/logic/validations.c
    src/logic/report_logic.c
)
target_include_directories(BankApp PRIVATE ./src)

# =======================
# Tests
# =======================

# TEST: Account Data
add_executable(test_account_data
    Tests/test_account_data.c
    Tests/unity/unity.c
    src/data/account_data.c
    src/logic/create_account.c
    src/logic/validations.c
    src/presentation/user_interface.c
    src/logic/delete_account.c
    src/logic/update_account.c
    src/logic/bank_logic.c
    src/data/transactions_db.c
)
target_include_directories(test_account_data PRIVATE ./src ./Tests)
add_test(NAME AccountDataTest COMMAND test_account_data)

# TEST: Account Number
add_executable(test_account_number
    Tests/test_account_number.c
    Tests/unity/unity.c
    src/data/account_data.c
    src/logic/create_account.c
    src/logic/delete_account.c
    src/logic/update_account.c
    src/logic/bank_logic.c
    src/logic/validations.c
    src/presentation/user_interface.c
    src/data/transactions_db.c
)
target_include_directories(test_account_number PRIVATE ./src ./Tests)
add_test(NAME AccountNumberTest COMMAND test_account_number)


# TEST: Report Logic
add_executable(test_report_logic
    Tests/test_report_logic.c
    Tests/unity/unity.c
    src/data/report_data.c
)
target_include_directories(test_report_logic PRIVATE ./src ./Tests)
add_test(NAME ReportLogicTest COMMAND test_report_logic)


# TEST: Create Account
add_executable(test_create_account
    Tests/test_create_account.c
    Tests/unity/unity.c
    src/data/account_data.c
    src/logic/create_account.c
    src/logic/validations.c
    src/presentation/user_interface.c
    src/logic/delete_account.c
    src/logic/update_account.c
    src/logic/bank_logic.c
    src/data/transactions_db.c
)
target_include_directories(test_create_account PRIVATE ./src ./Tests)
add_test(NAME CreateAccountTest COMMAND test_create_account)

# TEST: Update Account
add_executable(test_update_account
    Tests/test_update_account.c
    Tests/unity/unity.c
    src/data/account_data.c
    src/logic/create_account.c
    src/logic/validations.c
    src/presentation/user_interface.c
    src/logic/delete_account.c
    src/logic/update_account.c
    src/logic/bank_logic.c
    src/data/transactions_db.c
)
target_include_directories(test_update_account PRIVATE ./src ./Tests)
add_test(NAME UpdateAccountTest COMMAND test_update_account)

# TEST: Account Data with Mock
add_executable(test_account_data_mocked
        Tests/test_account_data_mocked.c
        Tests/unity/unity.c
        mocks/Mockaccount_data.c
        Tests/CMock/src/cmock.c
)
target_include_directories(test_account_data_mocked PRIVATE ./src ./Tests ./mocks)
add_test(NAME AccountDataTestMocked COMMAND test_account_data_mocked)

# TEST: Simple
add_executable(test_simple
    Tests/test_simple.c
    Tests/unity/unity.c
)
target_include_directories(test_simple PRIVATE ./src ./Tests)
add_test(NAME SimpleTest COMMAND test_simple)
