[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/RxH5GUXD)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=18372190&assignment_repo_type=AssignmentRepo)

# BANK-Teissl_A_BANKPROJECT

## Build with CMake
Follow these steps to build and run the project using **CMake**:
```sh
cmake -G "MinGW Makefiles" ..
mkdir -p build
cd build
cmake ..
cmake --build .
./BankApp
```
ruby Tests/CMock/lib/cmock.rb src/data/account_data.h

```
## Compile with GCC
To manually compile the project using **GCC**, run:
```sh
gcc -o BankProject src/main.c src/create_account.c src/account_number.c -I./include
```