#include "ui.h"
#include "user_management.h"
#include "job_management.h"
#include "application_management.h"

void showHeader() {
    printf(BOLD GREEN
           "\n=========================================================\n"
           "       CONSOLE-BASED JOB FINDER & RESUME MATCHER       \n"
           "=========================================================\n" RESET);
    printf(BLUE "A simplified console version inspired by modern job portals.\n" RESET);
}

void adminMenu() {
    if (!loggedInUser) return;
    int choice;
    do {
        printf(BOLD MAGENTA "\n==== ADMIN DASHBOARD ====\n" RESET);
        printf("1. Add New Job\n");
        printf("2. View All Jobs\n");
        printf("3. View Applicants for a Job\n");
        printf("4. Delete Job by ID\n");
        printf("5. Export Applications to CSV\n");
        printf("6. Edit My Profile\n");
        printf("7. Change My Password\n");
        printf("0. Logout\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            choice = -1; // Invalid input
        }
        while(getchar()!='\n');

        switch(choice) {
            case 1: addJobInteractive(); break;
            case 2: viewAllJobsInteractive(); break;
            case 3: viewApplicantsForJob(); break;
            case 4: deleteJobByID(); break;
            case 5: exportApplicationsCSV(); break;
            case 6: editProfile(); break;
            case 7: changePassword(); break;
            case 0: loggedInUser = NULL; printf(GREEN "Logged out successfully.\n" RESET); break;
            default: printf(YELLOW "Invalid choice. Please try again.\n" RESET);
        }
    } while (choice != 0);
}

void userMenu() {
    if (!loggedInUser) return;
    int choice;
    do {
        printf(BOLD CYAN "\n==== USER DASHBOARD ====\n" RESET);
        printf("1. Search Jobs & Apply\n");
        printf("2. View All Jobs\n");
        printf("3. Apply by Job ID\n");
        printf("4. View My Applications\n");
        printf("5. Edit My Profile\n");
        printf("6. Change My Password\n");
        printf("0. Logout\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        while(getchar()!='\n');

        switch(choice) {
            case 1: searchJobsInteractive(); break;
            case 2: viewAllJobsInteractive(); break;
            case 3: {
                printf("Enter Job ID to apply for: ");
                int id;
                if (scanf("%d", &id) == 1) {
                    applyForJobByID(id);
                }
                while(getchar()!='\n');
                break;
            }
            case 4: viewMyApplications(); break;
            case 5: editProfile(); break;
            case 6: changePassword(); break;
            case 0: loggedInUser = NULL; printf(GREEN "Logged out successfully.\n" RESET); break;
            default: printf(YELLOW "Invalid choice. Please try again.\n" RESET);
        }
    } while (choice != 0);
}

void mainMenuLoop() {
    int choice;
    do {
        showHeader();
        printf(BOLD "\n--- Main Menu ---\n" RESET);
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Register New User\n");
        printf("4. Browse All Jobs\n");
        printf("0. Save & Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            choice = -1; // Handle non-integer input
        }
        while(getchar()!='\n'); // Clear input buffer

        switch(choice) {
            case 1:
                if (loginInteractive(1)) adminMenu();
                break;
            case 2:
                if (loginInteractive(0)) userMenu();
                break;
            case 3:
                registerUserInteractive();
                break;
            case 4:
                viewAllJobsInteractive();
                break;
            case 0:
                // Exit condition
                break;
            default:
                printf(YELLOW "Invalid choice. Please try again.\n" RESET);
        }
    } while (choice != 0);
}