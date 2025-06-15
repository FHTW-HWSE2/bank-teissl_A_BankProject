#include <stdio.h>
#include <string.h>
#include "../logic/report_logic.h"

void request_financial_report() {
    printf("\n=== Financial Report Request ===\n");
    printf("Select report type:\n");
    printf("  [1] Total money in the bank\n");
    printf("  [2] Number of active accounts\n");
    printf("  [3] Detailed account information\n");
    printf("  [4] All reports\n");
    printf("Enter your choice (1-4): ");

    int choice;
    scanf("%d", &choice);

    if (choice < 1 || choice > 4) {
        printf("Error: Invalid choice.\n");
        return;
    }

    const char *report_types[] = {"total_money", "active_accounts", "account_details"};
    Report report;

    if (choice == 4) {
        // Generate and print all reports
        for (int i = 0; i < 3; i++) {
            if (generate_report(report_types[i], &report)) {
                printf("\n=== %s Report ===\n%s\n", report_types[i], report.data);

                // Append to report.txt
                FILE *file = fopen("report.txt", "a"); // append mode
                if (file) {
                    fprintf(file, "=== %s Report ===\n%s\n\n", report_types[i], report.data);
                    fclose(file);
                }
            } else {
                printf("\nError: No data for %s report.\n", report_types[i]);
            }
        }
        printf("All reports saved to report.txt\n");
    } else {
        const char *report_type = report_types[choice - 1];
        if (!generate_report_request(report_type)) {
            printf("Error: Invalid report parameters.\n");
            return;
        }

        if (generate_report(report_type, &report)) {
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
    }

    // Pause for user to see output
    printf("\nPress Enter to continue...");
    getchar(); // Clear leftover newline from scanf
    getchar(); // Wait for Enter key
}
