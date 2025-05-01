#ifndef DELETE_ACCOUNT_H
#define DELETE_ACCOUNT_H

/**
 * @brief Deletes an account by account number and archives it.
 * 
 * Loads the account, removes it from the active accounts file,
 * and archives it to a separate deleted accounts file.
 * 
 * @param account_number The account number to delete.
 * @return 0 on success, -1 if not found, -2 if deletion failed, -3 if archiving failed.
 */
int delete_account(const char *account_number);

#endif
