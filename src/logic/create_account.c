#include "unity.h"
#include "account_data.h"
#include "create_account.h"
#include "user_interface.h"

#include "../mocks/Mockaccount_data.h"
#include "Mockuser_interface.h"
#include "Mockcreate_account.h"


#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>




const char *filename = "../assets/accounts.csv";

void create_account_logic() {
    BankAccount account = {0};

    strcpy(account.account_number, generate_unique_account_number());
    start_account_creation_ui(&account);
    save_account_to_csv(filename, &account);
}

void start_account_creation_ui(BankAccount *account) {

    get_nonempty_input("First name: ", account->first_name, MAX_STRING_LENGTH);
    get_nonempty_input("Last name: ", account->last_name, MAX_STRING_LENGTH);
    get_nonempty_input("Address: ", account->address, MAX_STRING_LENGTH);
    get_nonempty_input("Phone: ", account->phone, MAX_STRING_LENGTH);
    get_nonempty_input("Email: ", account->email, MAX_STRING_LENGTH);

    get_validated_input("SSN (10 digits): ", account->ssn, sizeof(account->ssn), is_valid_ssn, "Invalid SSN. Must be 10 digits.");
    get_validated_input("Branch code (B1/B2): ", account->branch_code, sizeof(account->branch_code), is_valid_branch_code, "Invalid branch code. Use 'B1' or 'B2'.");

    print_account_confirmation(account);
}

char* generate_unique_account_number() {
    static char account_number[9];

    srand((unsigned int)time(NULL));
    do {
        snprintf(account_number, sizeof(account_number), "%08u", (unsigned)(rand() % 100000000));
        // Ensure the account number is unique
    } while (strcmp(account_number, "00000000") == 0 || account_exists(filename, account_number));
    return account_number;
}

// Validation logic moved from UI
int is_valid_ssn(const char *ssn) {
    if (strlen(ssn) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(ssn[i])) return 0;
    }
    return 1;
}

int is_valid_branch_code(const char *branch_code) {
    return (strcmp(branch_code, "B1") == 0 || strcmp(branch_code, "B2") == 0);
}
