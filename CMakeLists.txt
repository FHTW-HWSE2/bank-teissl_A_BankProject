cmake_minimum_required(VERSION 3.10)
project(BANK-Teissl_A_BANKPROJECT C)

set(CMAKE_C_STANDARD 99)

# Include header directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Build the executable with all source files
add_executable(BankApp src/main.c src/create_account.c src/account_number.c)
