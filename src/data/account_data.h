#ifndef ACCOUNT_DATA_H
#define ACCOUNT_DATA_H

#include "src/logic/create_account.h"
#include <stdbool.h>

/**
 * @brief Checks if an account with the given number exists in the file.
 * 
 * @param filename Path to the CSV file.
 * @param account_number The account number to check for.
 * @return true if account exists, false otherwise.
 */
bool account_exists(const char *filename, const char *account_number);

/**
 * @brief Appends a new account to the CSV file.
 * 
 * @param filename Path to the CSV file.
 * @param account Pointer to the BankAccount struct to save.
 * @return 0 on success, 1 if failed.
 */
int save_account_to_csv(const char *filename, const BankAccount *account);

/**
 * @brief Retrieves account data by account number.
 * 
 * @param account_number The account number to search for.
 * @param account Pointer to store the found account.
 * @return 0 if found, -1 if not found or file error.
 */
int get_account_by_account_number(const char *account_number, BankAccount *account);

/**
 * @brief Removes an account from the CSV file.
 * 
 * @param account Pointer to the account to remove.
 * @return 0 if removed, -1 if not found or file error.
 */
int remove_account(const BankAccount *account);

#endif