cmake_minimum_required(VERSION 3.10)
project(BANK-Teissl_A_BANKPROJECT C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

if(COVERAGE)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

add_custom_target(coverage
        COMMAND gcovr --root .. --object-directory . --filter '../src/' --html --html-details -o coverage.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

include_directories(${PROJECT_SOURCE_DIR})
add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)

enable_testing()

# 🔒 Glavna aplikacija – ne diraš!
add_executable(BankApp
        src/main.c
        src/presentation/user_interface.c
        src/data/account_data.c
        src/data/transactions_db.c
        src/logic/controller.c
        src/logic/delete_account.c
        src/logic/create_account.c
        src/logic/update_account.c
        src/logic/bank_logic.c
        src/logic/validations.c
)
target_include_directories(BankApp PRIVATE ./src)

# ✅ TEST: Validations
add_executable(test_validations
        Tests/test_validations.c
        Tests/unity/unity.c
        src/logic/validations.c
        src/presentation/user_interface.c
        src/logic/create_account.c
        src/logic/delete_account.c
        src/logic/update_account.c
        src/logic/bank_logic.c
        src/data/account_data.c
        src/data/transactions_db.c
)
target_include_directories(test_validations PRIVATE ./src ./Tests)
add_test(NAME ValidationsTest COMMAND test_validations)

# ✅ TEST: Account Data
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

# ✅ TEST: Transactions DB
add_executable(test_transactions_db
        Tests/test_transactions_db.c
        Tests/unity/unity.c
        src/data/transactions_db.c
        src/presentation/user_interface.c
        src/logic/create_account.c
        src/logic/delete_account.c
        src/logic/update_account.c
        src/logic/validations.c
        src/logic/bank_logic.c
        src/data/account_data.c
)
target_include_directories(test_transactions_db PRIVATE ./src ./Tests)
add_test(NAME TransactionsDBTest COMMAND test_transactions_db)

# ✅ TEST: Account Number
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

# ✅ TEST: Create Account
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

# ✅ TEST: Simple
add_executable(test_simple
        Tests/test_simple.c
        Tests/unity/unity.c
)
target_include_directories(test_simple PRIVATE ./src ./Tests)
add_test(NAME SimpleTest COMMAND test_simple)
