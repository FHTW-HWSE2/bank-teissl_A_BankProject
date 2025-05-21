cmake_minimum_required(VERSION 3.10)
project(BankProject C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/Tests
    ${PROJECT_SOURCE_DIR}/mocks
    ${PROJECT_SOURCE_DIR}/CMock-master/src
)

# === Optional: Generate Mocks with CMock ===
add_custom_target(GenerateMocks ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/mocks
    COMMAND ruby ${PROJECT_SOURCE_DIR}/CMock-master/lib/cmock.rb -o ${PROJECT_SOURCE_DIR}/mocks/Mockaccount_data.c ${PROJECT_SOURCE_DIR}/src/data/account_data.h
    COMMAND ruby ${PROJECT_SOURCE_DIR}/CMock-master/lib/cmock.rb -o ${PROJECT_SOURCE_DIR}/mocks/Mockuser_interface.c ${PROJECT_SOURCE_DIR}/src/presentation/user_interface.h
    COMMAND ruby ${PROJECT_SOURCE_DIR}/CMock-master/lib/cmock.rb -o ${PROJECT_SOURCE_DIR}/mocks/Mockcreate_account.c ${PROJECT_SOURCE_DIR}/src/logic/create_account.h
)


# === Main Application ===
add_executable(CreateAccountTestCmock
    ${MOCK_SOURCES}
    Tests/unity/src/unity.c
    Tests/test_create_account.c
)

# === Test Target with Unity + CMock ===
file(GLOB MOCK_SOURCES "${PROJECT_SOURCE_DIR}/mocks/*.c")

add_executable(CreateAccountTestCmock
    Tests/unity/src/unity.c
    ${MOCK_SOURCES}
    Tests/test_create_account.c
)

# Make sure mocks are generated first
add_dependencies(CreateAccountTestCmock GenerateMocks)

target_include_directories(CreateAccountTestCmock PRIVATE 
    ${PROJECT_SOURCE_DIR}/Tests/unity/src
    ${PROJECT_SOURCE_DIR}/mocks
    ${PROJECT_SOURCE_DIR}/src/data
    ${PROJECT_SOURCE_DIR}/src/logic
    ${PROJECT_SOURCE_DIR}/src/presentation
)

# === Enable and Register the Test ===
enable_testing()
add_test(NAME CreateAccountTestCmock COMMAND CreateAccountTestCmock)
