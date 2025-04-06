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

void save_account_to_csv(
    const char *first, const char *last, const char *ssn,
    const char *address, const char *phone, const char *email,
    const char *type, double balance, double overdraft,
    const char *branch, const char *account_number
) {
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
            first, last, ssn, address, phone, email, type, balance, overdraft, branch, account_number);
    fclose(file);
}
