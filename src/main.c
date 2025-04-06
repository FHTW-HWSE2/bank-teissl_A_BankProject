#include "include/presentation.h"

/**
 * @brief Main entry point of the program.
 *
 * This function initializes the application by calling create_bank_account(),
 * which sets up a new bank account. It then returns 0 to indicate successful execution.
 *
 * @return int Returns 0 if the program completes successfully.
 */
int main(void) {
    start_account_creation_ui();
    return 0;
}