#include <stdio.h>
#include <string.h>
#include "report_data.h"



// Helper: Read account data
int read_accounts_csv(Account accounts[], int max_accounts) {
    FILE *file = fopen("assets/accounts.csv", "r");
    if (!file) {
        printf("Error opening accounts.csv\n");
        return 0;
    }

    char line[256];
    int count = 0;

    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) && count < max_accounts) {
    sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%lf",
           accounts[count].first_name,
           accounts[count].last_name,
           accounts[count].ssn,
           accounts[count].address,
           accounts[count].phone,
           accounts[count].email,
           accounts[count].branch_code,
           accounts[count].account_number,
           &accounts[count].balance); 
    count++;
    }
    fclose(file);
    return count;
}

// Fetch report data
int fetch_report_data(const char *parameters, Report *report) {
    Account accounts[MAX_ACCOUNTS];
    int count = read_accounts_csv(accounts, MAX_ACCOUNTS);

    if (count == 0) {
        strcpy(report->data, "No data found");
        return 0;
    }

    if (strcmp(parameters, "total_money") == 0) {
        double total = 0;
        for (int i = 0; i < count; i++) {
           
            total += atof(accounts[i].account_number);
        }
        snprintf(report->data, sizeof(report->data), "Total Money in Bank: %.2f", total);
        return 1;

    } else if (strcmp(parameters, "active_accounts") == 0) {
        snprintf(report->data, sizeof(report->data), "Number of Active Accounts: %d", count);
        return 1;

    } else if (strcmp(parameters, "account_details") == 0) {
    strcpy(report->data, "Detailed Account Information:\n");
    for (int i = 0; i < count; i++) {
        char line[256];
        snprintf(line, sizeof(line),
                 "Name: %s %s, SSN: %s, Email: %s, Branch: %s\n",
                 accounts[i].first_name, accounts[i].last_name,
                 accounts[i].ssn, accounts[i].email,
                 accounts[i].branch_code);
        strcat(report->data, line);
    }
    return 1;
}


    strcpy(report->data, "Invalid report type");
    return 0;
}
