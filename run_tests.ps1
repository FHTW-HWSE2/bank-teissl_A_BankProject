# run_tests.ps1

# Navigate to build folder if needed
cd build

# Run CMake configuration
cmake ..

# Build project
cmake --build .

# Run the test
./test_account_data.exe
#./test_account_data_mocked.exe
