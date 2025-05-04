cmake_minimum_required(VERSION 3.10)
project(BANK-Teissl_A_BANKPROJECT C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# === Include Directories ===
include_directories(
    ${PROJECT_SOURCE_DIR}
    src/data
    src/logic
    src/presentation
    CMock-master/src
    Tests/unity/src
    mocks
)

# === Compiler Flags ===
add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)

enable_testing()

# === Main Application ===
add_executable(BankApp     
    src/main.c 
    src/data/account_data.c 
    src/presentation/user_interface.c 
    src/logic/create_account.c
)

# === Tests ===

# Unity + CMock + Real Code
add_executable(CreateAccountTest
    Tests/unity/src/unity.c
    CMock-master/src/cmock.c
    Tests/test_create_account.c
    src/data/account_data.c
    src/presentation/user_interface.c
    src/logic/create_account.c
)

add_test(NAME CreateAccountTest COMMAND CreateAccountTest)

# Unity + CMock + Mocks
add_executable(AccountNumberTestCmock
    Tests/unity/src/unity.c
    CMock-master/src/cmock.c
    Tests/test_account_number.c
    mocks/Mockaccount_data.c 
    mocks/Mockuser_interface.c
    mocks/Mockcreate_account.c
)

add_test(NAME AccountNumberTestCmock COMMAND AccountNumberTestCmock)
