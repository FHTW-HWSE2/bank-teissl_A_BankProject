cmake_minimum_required(VERSION 3.10)
project(BANK-Teissl_A_BANKPROJECT C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR})

add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)

enable_testing()

add_executable(BankApp
        src/main.c
        src/logic/controller.c
        src/logic/create_account.c
        src/logic/delete_account.c
        src/logic/update_account.c
        src/data/account_data.c
        src/presentation/user_interface.c
)
