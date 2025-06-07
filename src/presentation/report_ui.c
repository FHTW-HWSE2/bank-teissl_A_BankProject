#include <stdio.h>
#include <string.h>
#include "../logic/report_logic.h"

void request_financial_report() {
    printf("\n=== Financial Report Request ===\n");
    printf("Select report type:\n");
    printf("  [1] Total money in the bank\n");
    printf("  [2] Number of active accounts\n");
    printf("  [3] Detailed account information\n");
    printf("Enter your choice (1-3): ");

    int choice;
    scanf("%d", &choice);

    const char *report_type;

    switch (choice) {
        case 1:
            report_type = "total_money";
            break;
        case 2:
            report_type = "active_accounts";
            break;
        case 3:
            report_type = "account_details";
            break;
        default:
            printf("Error: Invalid choice.\n");
            return;
    }

    if (!generate_report_request(report_type)) {
        printf("Error: Invalid report parameters.\n");
        return;
    }

    Report report;
    if (generate_report(report_type, &report)) {
        // Show report on console
        printf("\n=== Report ===\n%s\n", report.data);

        // Save report to file
        FILE *file = fopen("report.txt", "w");
        if (file) {
            fprintf(file, "%s\n", report.data);
            fclose(file);
            printf("Report also saved to report.txt\n");
        } else {
            printf("Error: Could not save report to file.\n");
        }
    } else {
        printf("Error: No data available.\n");
    }

    // Pause for user to see the report before returning to the main menu
    printf("\nPress Enter to continue...");
    getchar(); // Clear leftover newline from scanf
    getchar(); // Wait for Enter key
}
