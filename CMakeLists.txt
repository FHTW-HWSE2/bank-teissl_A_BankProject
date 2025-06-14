cmake_minimum_required(VERSION 3.10)
project(BANK-Teissl_A_BANKPROJECT C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# ========== Coverage option ==========
option(COVERAGE "Enable code coverage" ON)

if(COVERAGE)
    message(STATUS "Building with coverage flags")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# ========== Coverage target ==========
add_custom_target(coverage
    COMMAND gcovr --root ${CMAKE_SOURCE_DIR} --object-directory . --filter "${CMAKE_SOURCE_DIR}/src" --html --html-details -o coverage.html
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# ========== Global includes & warnings ==========
include_directories(${PROJECT_SOURCE_DIR})
add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)

enable_testing()

# ========== Main Executable ==========
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

# ========== Helper Macro for Test Targets ==========
function(add_test_with_coverage name sources)
    add_executable(${name} ${sources})
    target_include_directories(${name} PRIVATE ./src ./Tests ./mocks)
    if(COVERAGE)
        target_compile_options(${name} PRIVATE --coverage -O0 -g)
        target_link_libraries(${name} PRIVATE gcov)
    endif()
    add_test(NAME ${name} COMMAND ${name})
endfunction()

# ========== Test Targets ==========
add_test_with_coverage(test_account_data
    "Tests/test_account_data.c;Tests/unity/unity.c;src/data/account_data.c;src/logic/create_account.c;src/logic/validations.c;src/presentation/user_interface.c;src/logic/delete_account.c;src/logic/update_account.c;src/logic/bank_logic.c;src/data/transactions_db.c"
)

add_test_with_coverage(test_account_number
    "Tests/test_account_number.c;Tests/unity/unity.c;src/data/account_data.c;src/logic/create_account.c;src/logic/delete_account.c;src/logic/update_account.c;src/logic/bank_logic.c;src/logic/validations.c;src/presentation/user_interface.c;src/data/transactions_db.c"
)

add_test_with_coverage(test_create_account
    "Tests/test_create_account.c;Tests/unity/unity.c;src/data/account_data.c;src/logic/create_account.c;src/logic/validations.c;src/presentation/user_interface.c;src/logic/delete_account.c;src/logic/update_account.c;src/logic/bank_logic.c;src/data/transactions_db.c"
)

add_test_with_coverage(test_delete_account
    "Tests/test_create_account.c;Tests/unity/unity.c;src/data/account_data.c;src/logic/create_account.c;src/logic/validations.c;src/presentation/user_interface.c;src/logic/delete_account.c;src/logic/update_account.c;src/logic/bank_logic.c;src/data/transactions_db.c"
)

add_test_with_coverage(test_account_data_mocked
    "Tests/test_account_data_mocked.c;Tests/unity/unity.c;mocks/Mockaccount_data.c;Tests/CMock/src/cmock.c"
)

add_test_with_coverage(test_simple
    "Tests/test_simple.c;Tests/unity/unity.c"
)
