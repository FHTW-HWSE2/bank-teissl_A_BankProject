cmake_minimum_required(VERSION 3.10)
project(BANK-TEISSL_A_BANKPROJECT C)

set(CMAKE_C_COMPILER "cl" CACHE STRING "C compiler" FORCE)  # For VS
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the main executable
add_executable(BANK-TEISSL_A_BANKPROJECT main.c)
