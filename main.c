#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NAME 50
#define MAX_SSN 12 // 10 digits + newline + '\0'
#define MAX_ADDRESS 100
#define MAX_PHONE 20
#define MAX_EMAIL 50
#define ACCOUNT_NUMBER_LENGTH 9

enum AccountType
{
    STANDARD_ACCOUNT = 1,
    BALANCE_ACCOUNT = 2,
    OVERDRAFT_LIMIT_ACCOUNT = 3
};

typedef struct
{
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char ssn[MAX_SSN];
    char address[MAX_ADDRESS];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
} Customer;

typedef struct
{
    Customer customer;
    enum AccountType accountType;
    float initialBalance;
    float overdraftLimit;
    char branch[3];
    char accountNumber[ACCOUNT_NUMBER_LENGTH];
} Account;

void strip_newline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

int is_empty(const char *str)
{
    return str[0] == '\0';
}

int is_numeric(const char *str)
{
    for (int i = 0; str[i]; i++)
    {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

int is_valid_email(const char *email)
{
    return strchr(email, '@') != NULL;
}

void read_required_input(const char *prompt, char *target, int max_length)
{
    do
    {
        printf("%s", prompt);
        fgets(target, max_length, stdin);
        strip_newline(target);

        if (is_empty(target))
        {
            printf("Error: This field cannot be empty.\n");
        }
    } while (is_empty(target));
}

void read_valid_email(char *email, int max_length)
{
    do
    {
        read_required_input("Email: ", email, max_length);
        if (!is_valid_email(email))
        {
            printf("Error: Invalid email. Must contain '@'.\n");
        }
    } while (!is_valid_email(email));
}

void read_valid_phone(char *phone, int max_length)
{
    do
    {
        read_required_input("Phone number: ", phone, max_length);
        if (!is_numeric(phone))
        {
            printf("Error: Phone number must contain only digits.\n");
        }
    } while (!is_numeric(phone));
}

void read_valid_ssn(char *ssn, int max_length)
{
    do
    {
        read_required_input("Social Security Number (10 digits): ", ssn, max_length);
        strip_newline(ssn);
        if (!is_numeric(ssn) || strlen(ssn) != 10)
        {
            printf("Error: SSN must be exactly 10 digits and contain only numbers.\n");
        }
    } while (!is_numeric(ssn) || strlen(ssn) != 10);
}

char *generateAccountNumber()
{
    static char number[ACCOUNT_NUMBER_LENGTH + 1];

    // Initialisiert den Zufallszahlengenerator mit der aktuellen Zeit als Seed.
    // um bei jedem Programmlauf unterschiedliche Zufallszahlen zu erzeugen.
    srand((unsigned int)time(NULL));

    while (1)
    {
        for (int i = 0; i < ACCOUNT_NUMBER_LENGTH; i++)
        {
            number[i] = '0' + (rand() % 10);
        }
        number[ACCOUNT_NUMBER_LENGTH] = '\0';

        if (strcmp(number, "00000000") != 0)
        {
            break;
        }
    }

    return number;
}

/*
void readBranchCode(enum BranchCode branch) {
    do {
        printf("Choose Branch: (B1) or (B2)\n");
        fgets(branch, 2,stdin);
        strip_newline(branch);
        if (branch != "B1" || branch != "B2") {
            printf("Please only choose B1 or B2\n");
        }
    } while (branch != "B1" || branch != "B2");
}
*/

int main()
{
    Customer new_customer;
    Account newAccount;

    printf("=== Create New Bank Account ===\n");
    read_required_input("First name: ", new_customer.first_name, MAX_NAME);
    read_required_input("Last name: ", new_customer.last_name, MAX_NAME);
    read_valid_ssn(new_customer.ssn, MAX_SSN);
    read_required_input("Address: ", new_customer.address, MAX_ADDRESS);
    read_valid_phone(new_customer.phone, MAX_PHONE);
    read_valid_email(new_customer.email, MAX_EMAIL);

    newAccount.customer = new_customer;

    // readBranchCode(newAccount.branch); TODO: fix
    strcpy(newAccount.branch, "B1");

    // Todo: put it in a function with validation / enum?
    printf("Choose Account type:\n1- Standard account, 2- Account with initial balance, 3- Account with overdraft limit\n");
    char accountType[2];
    fgets(accountType, sizeof(accountType), stdin);
    strip_newline(accountType);

    if (accountType[0] == '1')
    {
        newAccount.accountType = STANDARD_ACCOUNT;
    }
    else if (accountType[0] == '2')
    {
        newAccount.accountType = BALANCE_ACCOUNT;
        printf("Enter initial balance: \n");
        scanf("%f", &newAccount.initialBalance);
    }
    else if (accountType[0] == '3')
    {
        newAccount.accountType = OVERDRAFT_LIMIT_ACCOUNT;
        printf("Enter overdraft limit: \n");
        scanf("%f", &newAccount.overdraftLimit);
    }

    char *accNumber = generateAccountNumber();
    strncpy(newAccount.accountNumber, accNumber, ACCOUNT_NUMBER_LENGTH - 1);
    newAccount.accountNumber[8] = '\0';

    printf("\n--- Account Created Successfully ---\n");
    printf("First Name: %s\n", new_customer.first_name);
    printf("Last Name: %s\n", new_customer.last_name);
    printf("SSN: %s\n", new_customer.ssn);
    printf("Address: %s\n", new_customer.address);
    printf("Phone: %s\n", new_customer.phone);
    printf("Email: %s\n", new_customer.email);

    printf("Branch code: %s\n", newAccount.branch);
    printf("Account Type: %i\n", newAccount.accountType);
    printf("Account number: %s\n", newAccount.accountNumber);

    FILE *fAccounts = fopen("assets/accounts.csv", "a");
    if (fAccounts == NULL)
    {
        printf("Can't open accounts file.\n");
        return 1;
    }

    //fprintf(fAccounts, "FirstName,LastName,SSN,Address,phone,email,accountType,initialBalance,OverdraftLimit,BranchCode,AccountNumber\n");
    fprintf(fAccounts, "%s,%s,%s,%s,%s,%s,%d,%.2f,%.2f,%s,%s\n", newAccount.customer.first_name, newAccount.customer.last_name, newAccount.customer.ssn,
            newAccount.customer.address, newAccount.customer.phone, newAccount.customer.email, newAccount.accountType, newAccount.initialBalance,
            newAccount.overdraftLimit, newAccount.branch, newAccount.accountNumber);

    fclose(fAccounts);

    return 0;
}
