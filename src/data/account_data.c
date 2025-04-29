#include "account_data.h"
#include "src/logic/controller.h"
#include "src/logic/create_account.h"
#include "src/presentation/user_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSV_FILE "../assets/accounts.csv"

bool account_exists(const char *filename, const char *account_number) {
    FILE *file = fopen(filename, "r");
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

int save_account_to_csv(const char *filename, const BankAccount *account) {
    FILE *file = fopen(filename, "a+");
    if (!file) {
        open_file_error();
        return 0;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "FirstName,LastName,SSN,Address,phone,email,BranchCode,AccountNumber,Balance\n");
    }

    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%lu\n",
            account->first_name,
            account->last_name,
            account->ssn,
            account->address,
            account->phone,
            account->email,
            account->branch_code,
            account->account_number,
            account->balance);
    fclose(file);

    return 0;
}

int get_account_by_id(BankAccount *account) {
    FILE *file = fopen("assets.csv", "r");
    if (!file) return -1;

    BankAccount temp;

    while (fscanf(file, "%[^,],%lf\n", temp.account_number, temp.balance) != EOF) {
        if (strcmp(temp.account_number, account->account_number) == 0) {
            account->balance = temp.balance; // Update the passed account with data
            fclose(file);
            return 0; // Found
        }
    }
    
    fclose(file);
    return -1; // Not found
}

int remove_account(const char *account_number) {
    FILE *file = fopen("assets.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!file || !temp) return -1;

    BankAccount account;
    int found = 0;

    while (fscanf(file, "%[^,],%lf\n", account.account_number, account.balance) != EOF) {
        if (strcmp(account.account_number, account_number) != 0) {
            fprintf(temp, "%s,%.2lf\n", account.account_number, account.balance);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove("assets.csv");
    rename("temp.csv", "assets.csv");

    return found ? 0 : -1;
}
