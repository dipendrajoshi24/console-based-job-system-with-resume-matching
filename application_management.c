#include "application_management.h"
#include "file_handler.h"
#include "utils.h"

Application* createApplication(int jobID, const char* jobTitle, const char* applicantName, const char* applicantEmail, const char* applicantQual, const char* applicantCV) {
    Application* a = (Application*)malloc(sizeof(Application));
    if (!a){
        perror("Failed to allocate memory for Application");
        exit(EXIT_FAILURE);
    }
    a->jobID = jobID;
    strncpy(a->jobTitle, jobTitle, sizeof(a->jobTitle)-1); a->jobTitle[sizeof(a->jobTitle)-1] = '\0';
    strncpy(a->applicantName, applicantName, sizeof(a->applicantName)-1); a->applicantName[sizeof(a->applicantName)-1] = '\0';
    strncpy(a->applicantEmail, applicantEmail, sizeof(a->applicantEmail)-1); a->applicantEmail[sizeof(a->applicantEmail)-1] = '\0';
    strncpy(a->applicantQualification, applicantQual, sizeof(a->applicantQualification)-1); a->applicantQualification[sizeof(a->applicantQualification)-1] = '\0';
    strncpy(a->applicantCV, applicantCV, sizeof(a->applicantCV)-1); a->applicantCV[sizeof(a->applicantCV)-1] = '\0';
    
    a->next = applicationList;
    applicationList = a;
    return a;
}

void applyForJobByID(int id) {
    if (!loggedInUser) {
        printf(RED "You must be logged in to apply.\n" RESET);
        return;
    }
    Job* j = jobList;
    while (j) {
        if (j->jobID == id) break;
        j = j->next;
    }
    if (!j) {
        printf(RED "Job with ID %d not found.\n" RESET, id);
        return;
    }

    // Check if already applied
    Application* app = applicationList;
    while(app) {
        if(app->jobID == id && strcmp(app->applicantEmail, loggedInUser->email) == 0) {
            printf(YELLOW "You have already applied for this job.\n" RESET);
            return;
        }
        app = app->next;
    }

    createApplication(j->jobID, j->title, loggedInUser->name, loggedInUser->email, loggedInUser->qualification, loggedInUser->cvLink);
    saveApplicationsToFile();
    printf(GREEN "Successfully applied to '%s'.\n" RESET, j->title);
}
void viewApplicantsForJob() {
    if (!jobList) {
        printf(YELLOW "No jobs exist.\n" RESET);
        return;
    }
    int id;
    printf(CYAN "\n=== View Applicants (Admin) ===\n" RESET);
    printf("Enter Job ID: ");
    scanf("%d", &id);
    while(getchar()!='\n');

    int found = 0;
    Application* a = applicationList;
    while (a) {
        if (a->jobID == id) {
            if (!found) {
                printf(GREEN "\nApplicants for Job ID %d - %s:\n" RESET, id, a->jobTitle);
                found = 1;
            }
            printf(" -> Name: %s | Email: %s | Qualification: %s | CV: %s\n", a->applicantName, a->applicantEmail, a->applicantQualification, a->applicantCV);
        }
        a = a->next;
    }
    if (!found) printf(YELLOW "No applicants found for this job ID.\n" RESET);
}
void exportApplicationsCSV() {
    saveApplicationsToFile();
    printf(GREEN "Applications data has been saved/updated in '%s'.\nYou can open this file with any spreadsheet software like Excel.\n" RESET, APPS_FILE);
}

void viewMyApplications() {
    if (!loggedInUser) {
        printf(RED "You must be logged in to view your applications.\n" RESET);
        return;
    }
    int found = 0;
    Application* a = applicationList;
    printf(CYAN "\n=== My Applications ===\n" RESET);
    while (a) {
        if (strcmp(a->applicantEmail, loggedInUser->email) == 0) {
            printf(" -> Job ID: %-5d | Title: %s\n", a->jobID, a->jobTitle);
            found = 1;
        }
        a = a->next;
    }
    if (!found) printf(YELLOW "You have not applied to any jobs yet.\n" RESET);
}