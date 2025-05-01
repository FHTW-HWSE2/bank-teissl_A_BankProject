#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#include "controller.h"

/**
 * @brief Handles the logic for creating a new bank account.
 */
void create_account_logic();

/**
 * @brief Guides the user through the account creation input process.
 * 
 * @param account Pointer to the account being created.
 */
void start_account_creation_ui(BankAccount *account);

/**
 * @brief Generates a unique 8-digit account number.
 * 
 * @return Pointer to the generated account number string.
 */
char* generate_unique_account_number(void);

/**
 * @brief Validates that the SSN consists of exactly 10 digits.
 * 
 * @param ssn The SSN string to validate.
 * @return 1 if valid, 0 otherwise.
 */
int is_valid_ssn(const char *ssn);

/**
 * @brief Checks if the given branch code is valid (B1 or B2).
 * 
 * @param branch_code The branch code to validate.
 * @return 1 if valid, 0 otherwise.
 */
int is_valid_branch_code(const char *branch_code);

#endif
