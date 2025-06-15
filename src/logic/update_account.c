#include "update_account.h"
#include "src/data/account_data.h"
#include "src/presentation/user_interface.h"
#include "src/logic/validations.h"
#include <stdio.h>
#include <string.h>



/**
 * @brief Updates the information of an existing account in the CSV file.
 *
 * @param filename Path to the CSV file containing the accounts.
 * @param account_number The account number to update.
 * @return int 0 if success, -1 if account not found, -2 if deletion failed, -3 if save failed.
 */
int update_account(const char *filename, const char *account_number) {
    BankAccount account;

    // Check if file exists and contains the account
    if (get_account_by_account_number(filename, account_number, &account) != 0) {
        return -1; // account not found or file doesn't exist
    }

    // Get updated data
    get_nonempty_input("New First Name: ", account.first_name);
    get_nonempty_input("New Last Name: ", account.last_name);
    get_nonempty_input("Address: ", account.address);
    get_nonempty_input("Phone: ", account.phone);
    get_nonempty_input("Email: ", account.email);
    get_validated_input("New Branch Code (B1/B2): ", account.branch_code, sizeof(account.branch_code), is_valid_branch_code, "Invalid branch code.");

    // Remove old account
    if (remove_account(filename, &account) != 0) {
        return -2; // failed to remove old record
    }

    // Save updated account
    if (save_account_to_csv(filename, &account) != 0) {
        return -3; // failed to save
    }

    return 0; // success
}
