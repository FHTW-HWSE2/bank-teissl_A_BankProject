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
// TODo return 1
int save_account_to_csv(const char *filename, const BankAccount *account) {
    FILE *file = fopen(filename, "a+");
    if (!file) {
        open_file_error();
        return -1;
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

int get_account_by_account_number(const char *account_number, BankAccount *account) {
    FILE *file = fopen(CSV_FILE, "r");

    if (!file) return -1;

    BankAccount temp;

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%lu\n",
                  temp.first_name,
                  temp.last_name,
                  temp.ssn,
                  temp.address,
                  temp.phone,
                  temp.email,
                  temp.branch_code,
                  temp.account_number,
                  &temp.balance) != EOF) {

        if (strcmp(temp.account_number, account_number) == 0) {
            *account = temp;  // copy all fields to caller
            fclose(file);
            return 0; // Found
        }
    }

    fclose(file);
    return -1; // Not found
}

int remove_account(const BankAccount *account) {
    FILE *file = fopen(CSV_FILE, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!file || !temp) return -1;

    BankAccount current;
    int found = 0;

    // ✅ Read the header line from the original file
    char header[512];
    if (fgets(header, sizeof(header), file)) {
        fputs(header, temp);  // ✅ Write the same header to the temp file
    }

    // Now read and process the remaining data rows
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%lu\n",
                  current.first_name,
                  current.last_name,
                  current.ssn,
                  current.address,
                  current.phone,
                  current.email,
                  current.branch_code,
                  current.account_number,
                  &current.balance) != EOF) {

        if (strcmp(current.account_number, account->account_number) != 0) {
            // Copy all fields to temp (preserve record)
            fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%s,%lu\n",
                    current.first_name,
                    current.last_name,
                    current.ssn,
                    current.address,
                    current.phone,
                    current.email,
                    current.branch_code,
                    current.account_number,
                    current.balance);
        } else {
            found = 1; // This is the account we're deleting
        }
    }

    fclose(file);
    fclose(temp);

    remove(CSV_FILE);
    rename("temp.csv", CSV_FILE);

    return found ? 0 : -1;
}
