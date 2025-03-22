#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 50
#define MAX_SSN 12      // 10 digits + newline + '\0'
#define MAX_ADDRESS 100
#define MAX_PHONE 20
#define MAX_EMAIL 50

typedef struct {
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char ssn[MAX_SSN];
    char address[MAX_ADDRESS];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
} Customer;

void strip_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int is_empty(const char *str) {
    return str[0] == '\0';
}

int is_numeric(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int is_valid_email(const char *email) {
 return strchr(email, '@') != NULL;
} 

void read_required_input(const char *prompt, char *target, int max_length) {
    do {
        printf("%s", prompt);
        fgets(target, max_length, stdin);
        strip_newline(target);

        if (is_empty(target)) {
            printf("Error: This field cannot be empty.\n");
        }
    } while (is_empty(target));
}

void read_valid_email(char *email, int max_length) {
    do {
        read_required_input("Email: ", email, max_length);
        if (!is_valid_email(email)) {
            printf("Error: Invalid email. Must contain '@'.\n");
        }
    } while (!is_valid_email(email));
}

void read_valid_phone(char *phone, int max_length) {
    do {
        read_required_input("Phone number: ", phone, max_length);
        if (!is_numeric(phone)) {
            printf("Error: Phone number must contain only digits.\n");
        }
    } while (!is_numeric(phone));
}

void read_valid_ssn(char *ssn, int max_length) {
    do {
        read_required_input("Social Security Number (10 digits): ", ssn, max_length);
        strip_newline(ssn);
        if (!is_numeric(ssn) || strlen(ssn) != 10) {
            printf("Error: SSN must be exactly 10 digits and contain only numbers.\n");
        }
    } while (!is_numeric(ssn) || strlen(ssn) != 10);
}

int main() {
    Customer new_customer;

    printf("=== Create New Bank Account ===\n");

    read_required_input("First name: ", new_customer.first_name, MAX_NAME);
    read_required_input("Last name: ", new_customer.last_name, MAX_NAME);
    read_valid_ssn(new_customer.ssn, MAX_SSN);
    read_required_input("Address: ", new_customer.address, MAX_ADDRESS);
    read_valid_phone(new_customer.phone, MAX_PHONE);
    read_valid_email(new_customer.email, MAX_EMAIL);

    printf("\n--- Account Created Successfully ---\n");
    printf("Name: %s\n", new_customer.first_name);
    printf("SSN: %s\n", new_customer.last_name);
    printf("SSN: %s\n", new_customer.ssn);
    printf("Address: %s\n", new_customer.address);
    printf("Phone: %s\n", new_customer.phone);
    printf("Email: %s\n", new_customer.email);

    return 0;
}
