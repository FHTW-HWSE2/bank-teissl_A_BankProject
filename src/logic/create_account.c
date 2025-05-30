#include "controller.h"
#include "create_account.h"
#include "src/data/account_data.h"
#include "src/presentation/user_interface.h"
#include "src/logic/validations.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>

const char *filename = "../assets/accounts.csv";

int create_account_logic() {
    BankAccount account = {0};

    strcpy(account.account_number, generate_unique_account_number());
    start_account_creation_ui(&account);
    if (save_account_to_csv(filename, &account) != 0)
    {
        printf("Error saving account to file.\n");
        return -1;
    }
    
    print_account_confirmation(&account);

    return 0;
}

void start_account_creation_ui(BankAccount *account) {

    get_nonempty_input("First name: ", account->first_name);
    get_nonempty_input("Last name: ", account->last_name);
    get_nonempty_input("Address: ", account->address);
    get_validated_input("Phone: ", account->phone, sizeof(account->phone), is_valid_phone_number, "Invalid Phone number. Must be just numbers.");
    get_validated_input("Email: ", account->email, sizeof(account->email), is_valid_email, "Invalid email.");
    get_validated_input("SSN (10 digits): ", account->ssn, sizeof(account->ssn), is_valid_ssn, "Invalid SSN. Must be 10 digits.");
    get_validated_input("Branch code (B1/B2): ", account->branch_code, sizeof(account->branch_code), is_valid_branch_code, "Invalid branch code. Use 'B1' or 'B2'.");
    account->branch_code[0] = toupper((unsigned char)account->branch_code[0]);
    account->balance = 0; // Initialize balance to 0
}

char* generate_unique_account_number() {
    static char account_number[9];

    srand((unsigned int)time(NULL));
    do {
        snprintf(account_number, sizeof(account_number), "%08d", rand() % 100000000);
    } while (strcmp(account_number, "00000000") == 0 || account_exists(filename, account_number));
    return account_number;
}
