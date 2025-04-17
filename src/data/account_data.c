#include "account_data.h"
#include "src/logic/create_account.h"
#include "src/presentation/user_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSV_FILE "../assets/accounts.csv"

bool account_exists(const char *account_number) {
    FILE *file = fopen(CSV_FILE, "r");
    if (!file) return false;

    char line[256];
    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file)) {
        char *token, *last = NULL;
        token = strtok(line, ",");
        while (token != NULL) {
            last = token;
            token = strtok(NULL, ",");
        }
        if (last) {
            last[strcspn(last, "\n")] = 0;
            if (strcmp(last, account_number) == 0) {
                fclose(file);
                return true;
            }
        }
    }
    fclose(file);
    return false;
}

void save_account_to_csv(const BankAccount *account) {
    FILE *file = fopen(CSV_FILE, "a+");
    if (!file) {
        open_file_error();
        return;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "FirstName,LastName,SSN,Address,phone,email,BranchCode,AccountNumber\n");
    }

    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s\n",
            account->first_name,
            account->last_name,
            account->ssn,
            account->address,
            account->phone,
            account->email,
            account->branch_code,
            account->account_number);
    fclose(file);
}
