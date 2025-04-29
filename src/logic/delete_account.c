#include "controller.h"
#include "delete_account.h"
#include "src/data/account_data.h"
#include "src/presentation/user_interface.h"
#include <stdio.h>
#include <stdlib.h>

#define DELETED_ACCOUNTS_FILE "../assets/deleted_accounts.csv"

int delete_account() {
    BankAccount account;
    
    // Step 1: Load account
    if (get_account_by_id(&account) != 0) {
        return -1; // Error: account not found
    }

    // Step 3: Remove from active accounts
    if (remove_account(account.account_number) != 0) {
        return -2; // Error deleting account
    }

    // Step 4: Archive to deleted_accounts.csv
    if (save_account_to_csv(DELETED_ACCOUNTS_FILE, &account) != 0) {
        return -3; // Error archiving deleted account
    }

    return 0;
}
