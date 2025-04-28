cmake_minimum_required(VERSION 3.10)
project(BANK-Teissl_A_BANKPROJECT C)

#project(BANK-Teissl_A_BANKPROJECT 
#   VERSION 1.0 
#   DESCRIPTION "Bank system for account management, transactions, reporting, and clerk operations." 
#   LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)


# Include header directory
include_directories(${PROJECT_SOURCE_DIR}
    Tests/CMock/src
    src/data
)
#include_directories(Tests/mocks)
#include_directories(Tests/CMock)

# Add custom compiler flags
add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)

enable_testing()

# Build the executable with all source files
add_executable(BankApp     
                src/main.c 
                src/data/account_data.c 
                src/presentation/user_interface.c 
                src/logic/create_account.c
                )

add_executable(AccountNumberTest
                Tests/unity/src/unity.c           
                Tests/test_account_number.c 
                Tests/CMock/src/cmock.c
                src/data/account_data.c 
                src/presentation/user_interface.c 
                src/logic/create_account.c
                )

add_test(NAME AccountNumberTest COMMAND test_account_number)

add_executable(AccountNumberTestCmock
                Tests/unity/src/unity.c         
                Tests/test_account_number.c 
                Tests/CMock/src/cmock.c
                mocks/Mockaccount_data.c 
                mocks/Mockuser_interface.c
                mocks/Mockcreate_account.c
                )

add_test(NAME AccountNumberTestCmock COMMAND test_account_number_cmock)

add_executable(CreateAccountTest
                Tests/unity/src/unity.c         
                Tests/test_create_account.c 
                Tests/CMock/src/cmock.c
                src/data/account_data.c 
                src/presentation/user_interface.c 
                src/logic/create_account.c
                )

add_test(NAME CreateAccountTest COMMAND test_create_account)
