#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define STATUS_LEN 12
#define INPUT_SIZE 30

typedef struct {
    char account_number[20];       // fixed value, cannot be changed
    char ssn[15];                  // fixed value, cannot be changed
    int overdraft_limit_cents;     // in cents (e.g. 1000 = 10.00€)
    char status[STATUS_LEN];       // "active" or "inactive"
} Account;

// removes newline character from string input
void strip_newline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

// checks if string contains only digits
int is_numeric(const char *s) {
    for (int i = 0; s[i]; i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}

// allows user to update overdraft and status only
void update_account(Account *acc) {
    char input[INPUT_SIZE];
    int new_limit;
    char new_status[STATUS_LEN];

    printf("\n=== Update Account ===\n");

    // fixed fields
    printf("Account Number: %s (not editable)\n", acc->account_number);
    printf("SSN: %s (not editable)\n", acc->ssn);

    // update overdraft limit
    printf("Current Overdraft Limit (in cents): %d\n", acc->overdraft_limit_cents);
    printf("Enter new overdraft limit (in cents): ");
    fgets(input, sizeof(input), stdin);
    strip_newline(input);

    if (is_numeric(input)) {
        new_limit = atoi(input);
        if (new_limit >= 0) {
            acc->overdraft_limit_cents = new_limit;
        } else {
            printf("Limit can't be negative. Value not changed.\n");
        }
    } else {
        printf("Invalid input. Overdraft limit not updated.\n");
    }

    // update status
    printf("Current Status: %s\n", acc->status);
    printf("Enter new status (active/inactive): ");
    fgets(new_status, sizeof(new_status), stdin);
    strip_newline(new_status);

    if (strcmp(new_status, "active") == 0 || strcmp(new_status, "inactive") == 0) {
        strcpy(acc->status, new_status);
    } else {
        printf("Invalid status. Status not changed.\n");
    }

    // display updated info
    printf("\n--- Updated Account Information ---\n");
    printf("Account Number: %s\n", acc->account_number);
    printf("SSN: %s\n", acc->ssn);
    printf("Overdraft Limit: %d cents\n", acc->overdraft_limit_cents);
    printf("Status: %s\n", acc->status);
}

// test function
int main() {
    // sample test data
    Account acc = {
        .account_number = "ACC102938",
        .ssn = "1234567890",
        .overdraft_limit_cents = 10000,
        .status = "active"
    };

    update_account(&acc);

    return 0;
}
