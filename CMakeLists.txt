cmake_minimum_required(VERSION 3.10)
project(BANK-Teissl_A_BANKPROJECT C)

#project(BANK-Teissl_A_BANKPROJECT 
#   VERSION 1.0 
#   DESCRIPTION "Bank system for account management, transactions, reporting, and clerk operations." 
#   LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

if(COVERAGE)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

add_custom_target(coverage
COMMAND gcovr --root .. --object-directory . --filter '../src/' --html --html-details -o coverage.html
WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

# Include header directory
include_directories(${PROJECT_SOURCE_DIR})

# Add custom compiler flags
add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)

enable_testing()

# Build the executable with all source files
add_executable(BankApp     
                src/main.c 
                src/logic/controller.c
                src/logic/delete_account.c
                src/logic/create_account.c
                src/logic/update_account.c
                src/data/account_data.c 
                src/presentation/user_interface.c
                src/logic/bank_logic.c
                src/data/transactions_db.c
)

#add_executable(AccountNumberTest
#                Tests/unity/src/unity.c            # <-- if you use Unity for unit tests
#                Tests/test_account_number.c 
#                Tests/CMock/src/cmock.c
#                src/data/account_data.c 
#                src/presentation/user_interface.c 
#                src/logic/create_account.c
#                )

#add_test(NAME AccountNumberTest COMMAND test_account_number)

#add_executable(CreateAccountTest
#                Tests/unity/src/unity.c            # <-- if you use Unity for unit tests
#                Tests/test_create_account.c 
#                Tests/CMock/src/cmock.c
#                src/data/account_data.c 
#                src/presentation/user_interface.c 
#                src/logic/create_account.c
#                )

#add_test(NAME CreateAccountTest COMMAND test_create_account)
