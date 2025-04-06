cmake_minimum_required(VERSION 3.10)
project(BANK-Teissl_A_BANKPROJECT C)

#project(BANK-Teissl_A_BANKPROJECT 
#   VERSION 1.0 
#   DESCRIPTION "Bank system for account management, transactions, reporting, and clerk operations." 
#   LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)


# Include header directory
include_directories(${PROJECT_SOURCE_DIR})

# Add custom compiler flags
add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)

# Build the executable with all source files
add_executable(BankApp src/main.c src/account_data.c src/presentation.c src/create_account_logic.c)
