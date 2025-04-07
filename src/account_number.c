#include "include/account_number.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


#define CSV_FILE "../assets/accounts.csv"

// Checks if an account number exists in the CSV file by scanning the last field of each row.
 bool account_exists(const char *account_number) {
    FILE *file = fopen(CSV_FILE, "r");
    if (file == NULL) {
        return false;
    }
    char line[256];
    // Read and skip the header line (if present)
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return false;
    }
    while (fgets(line, sizeof(line), file)) {
        char *token;
        char *lastToken = NULL;
        token = strtok(line, ",");
        while (token != NULL) {
            lastToken = token;
            token = strtok(NULL, ",");
        }
        if (lastToken != NULL) {
            lastToken[strcspn(lastToken, "\n")] = '\0';
            if (strcmp(lastToken, account_number) == 0) {
                fclose(file);
                return true;
            }
        }
    }
    fclose(file);
    return false;
}

// Generates an 8-digit numeric string that is not "00000000" and unique in the CSV.
char* generate_unique_account_number(void) {
    static char account_number[9]; // 8 digits + null terminator
    srand((unsigned int)time(NULL));
    do {
        snprintf(account_number, sizeof(account_number), "%08d", rand() % 100000000);
    } while (strcmp(account_number, "00000000") == 0 || account_exists(account_number));
    return account_number;
}
