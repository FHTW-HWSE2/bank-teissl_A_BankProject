#include "include/account_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define CSV_FILE "../assets/accounts.csv"

static bool account_exists(const char *account_number) {
    FILE *file = fopen(CSV_FILE, "r");
    if (!file) return false;
    char line[256];
    fgets(line, sizeof(line), file); // skip header
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

char* generate_unique_account_number(void) {
    static char account_number[9];
    srand((unsigned int)time(NULL));
    do {
        snprintf(account_number, sizeof(account_number), "%08d", rand() % 100000000);
    } while (strcmp(account_number, "00000000") == 0 || account_exists(account_number));
    return account_number;
}

void save_account_to_csv(const BankAccount *account) {
    FILE *file = fopen(CSV_FILE, "a+");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "FirstName,LastName,SSN,Address,phone,email,accountType,initialBalance,OverdraftLimit,BranchCode,AccountNumber\n");
    }

    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%.2f,%.2f,%s,%s\n",
            account->first_name,
            account->last_name,
            account->ssn,
            account->address,
            account->phone,
            account->email,
            account->account_type,
            account->initial_balance,
            account->overdraft_limit,
            account->branch_code,
            account->account_number);
    fclose(file);
}
