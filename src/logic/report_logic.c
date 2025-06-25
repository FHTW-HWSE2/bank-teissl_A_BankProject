#include <string.h>
#include "report_logic.h"
#include "../data/report_data.h"

#define ACCOUNT_CSV_PATH "../assets/accounts.csv"

// Validate input parameters
int validate_parameters(const char *parameters) {
    if (strcmp(parameters, "total_money") == 0 ||
        strcmp(parameters, "active_accounts") == 0 ||
        strcmp(parameters, "account_details") == 0) {
        return 1; // Valid
    }
    return 0; // Invalid
}

// Generate report request
int generate_report_request(const char *parameters) {
    return validate_parameters(parameters);
}

// Generate report
int generate_report(const char *parameters, Report *report) {
    if (!validate_parameters(parameters)) {
        return 0;
    }

    if (fetch_report_data(ACCOUNT_CSV_PATH, parameters, report)) {
        return 1;
    } else {
        return 0; // No data found
    }
}
