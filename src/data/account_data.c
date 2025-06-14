#include "account_data.h"
#include "src/logic/controller.h"
#include "src/logic/create_account.h"
#include "src/presentation/user_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// TODO: Return 1 on success
int save_account_to_csv(const char *filename, const BankAccount *account) {
    FILE *file = fopen(filename, "a+");
    if (!file) {
        perror("fopen failed");
        print_message("Error opening file.");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "FirstName,LastName,SSN,Address,phone,email,BranchCode,Balance,AccountNumber\n");
    }

    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%lu,%s\n",
            account->first_name,
            account->last_name,
            account->ssn,
            account->address,
            account->phone,
            account->email,
            account->branch_code,
            account->balance,
            account->account_number);

    fclose(file);
    return 0;
}

int get_account_by_account_number(const char *filename, const char *account_number, BankAccount *account) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        BankAccount temp;
        memset(&temp, 0, sizeof(temp));

        // Remove newline
        line[strcspn(line, "\r\n")] = '\0';

        int parsed = sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%lu,%[^,\n]",
                            temp.first_name,
                            temp.last_name,
                            temp.ssn,
                            temp.address,
                            temp.phone,
                            temp.email,
                            temp.branch_code,
                            &temp.balance,
                            temp.account_number);

        if (parsed != 9) {
            continue;
        }


        if (strcmp(temp.account_number, account_number) == 0) {
            *account = temp;
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return -1; // Account not found
}

int remove_account(const char *filename, const BankAccount *account) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!file || !temp) return -1;

    char header[512];
    if (fgets(header, sizeof(header), file)) {
        fputs(header, temp);
    }

    BankAccount current;
    int found = 0;

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%lu,%[^,\n]\n",
                  current.first_name,
                  current.last_name,
                  current.ssn,
                  current.address,
                  current.phone,
                  current.email,
                  current.branch_code,
                  &current.balance,
                  current.account_number) != EOF) {

        if (strcmp(current.account_number, account->account_number) != 0) {
            fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%lu,%s\n",
                    current.first_name,
                    current.last_name,
                    current.ssn,
                    current.address,
                    current.phone,
                    current.email,
                    current.branch_code,
                    current.balance,
                    current.account_number);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(filename);
    rename("temp.csv", filename);

    return found ? 0 : -1;
}
