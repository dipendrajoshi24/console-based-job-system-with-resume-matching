#include "job_management.h"
#include "application_management.h"
#include "file_handler.h"
#include "utils.h"

int nextJobID() {
    int max = 0;
    Job* t = jobList;
    while (t) {
        if (t->jobID > max) max = t->jobID;
        t = t->next;
    }
    return max + 1;
}

Job* createJob(int jobID, const char* title, const char* company, const char* description, const char* requiredSkills, const char* requiredQualification, int priority) {
    Job* j = (Job*)malloc(sizeof(Job));
    if (!j) {
        perror("Failed to allocate memory for Job");
        exit(EXIT_FAILURE);
    }
    j->jobID = jobID;
    strncpy(j->title, title, sizeof(j->title)-1); j->title[sizeof(j->title)-1] = '\0';
    strncpy(j->company, company, sizeof(j->company)-1); j->company[sizeof(j->company)-1] = '\0';
    strncpy(j->description, description, sizeof(j->description)-1); j->description[sizeof(j->description)-1] = '\0';
    strncpy(j->requiredSkills, requiredSkills, sizeof(j->requiredSkills)-1); j->requiredSkills[sizeof(j->requiredSkills)-1] = '\0';
    strncpy(j->requiredQualification, requiredQualification, sizeof(j->requiredQualification)-1); j->requiredQualification[sizeof(j->requiredQualification)-1] = '\0';
    j->priority = priority;
    j->next = NULL;

    if (!jobList || j->priority > jobList->priority) {
        j->next = jobList;
        jobList = j;
    } else {
        Job* temp = jobList;
        while (temp->next && temp->next->priority >= j->priority) {
            temp = temp->next;
        }
        j->next = temp->next;
        temp->next = j;
    }
    return j;
}

void addJobInteractive() {
    char title[128], company[64], desc[512], skills[256], qual[64];
    int priority;
    printf(CYAN "\n=== Add Job (Admin) ===\n" RESET);
    int id = nextJobID();
    printf("Auto Job ID: %d\n", id);
    printf("Title: "); inputLine(title, sizeof(title));
    printf("Company: "); inputLine(company, sizeof(company));
    printf("Description: "); inputLine(desc, sizeof(desc));
    printf("Required skills (comma separated): "); inputLine(skills, sizeof(skills));
    printf("Required qualification: "); inputLine(qual, sizeof(qual));
    printf("Priority (1 low - 10 high): "); 
    scanf("%d", &priority); 
    while(getchar()!='\n'); // Clear input buffer

    createJob(id, title, company, desc, skills, qual, priority);
    saveJobsToFile();
    printf(GREEN "Job added with ID %d.\n" RESET, id);
}

void printJob(const Job* j) {
    if (!j) return;
    printf(BOLD BLUE "\n=================================================\n" RESET);
    printf(BOLD "%s" RESET " at " BOLD "%s\n" RESET, j->title, j->company);
    printf("Job ID: %d | Priority: %d\n", j->jobID, j->priority);
    printf(MAGENTA "Required Skills: " RESET "%s\n", j->requiredSkills);
    printf(MAGENTA "Qualification: " RESET "%s\n", j->requiredQualification);
    printf("Description: %s\n", j->description);
    printf(BOLD BLUE "====================================================\n" RESET);
}

void viewAllJobsInteractive() {
    if (!jobList) {
        printf(YELLOW "No jobs posted yet.\n" RESET);
        return;
    }
    Job* t = jobList;
    printf(CYAN "\n=== All Jobs (sorted by priority) ===\n" RESET);
    while (t) {
        printJob(t);
        t = t->next;
    }
}

void searchJobsInteractive() {
    if (!jobList) {
        printf(YELLOW "No jobs available to search.\n" RESET);
        return;
    }
    char query[256];
    printf(CYAN "\n=== Search Jobs (by skills, title, or company) ===\n" RESET);
    printf("Enter search query (leave blank to see recommendations): ");
    inputLine(query, sizeof(query));
    trim(query);

    Job* t = jobList;
    int found = 0;
    while (t) {
        int show = 0;
        if (strlen(query) == 0) {
            show = 1; // Show all if query is empty
        } else {
            char combined[1024];
            char queryLower[256];
            strncpy(queryLower, query, sizeof(queryLower)-1);
            queryLower[sizeof(queryLower)-1] = '\0';
            toLowerCase(queryLower);

            snprintf(combined, sizeof(combined), "%s %s %s", t->title, t->company, t->requiredSkills);
            toLowerCase(combined);
            if (strstr(combined, queryLower)) {
                show = 1;
            }
        }

        if (show) {
            found = 1;
            int match = 0;
            if (loggedInUser) {
                match = matchPercentage(loggedInUser->skills, t->requiredSkills, loggedInUser->qualification, t->requiredQualification);
            }
            printf(BOLD GREEN "\nJob ID: %d | %s at %s" RESET, t->jobID, t->title, t->company);
            if (match > 0) {
                printf(" | Your Match: " YELLOW "%d%%" RESET, match);
            }
            printf("\n  Skills: %s\n  Qualification: %s\n", t->requiredSkills, t->requiredQualification);
        }
        t = t->next;
    }

    if (!found) {
        printf(YELLOW "No jobs matched your search.\n" RESET);
    } else {
        printf(CYAN "\n(Type 'view <id>' for full description or 'apply <id>' to apply)\n" RESET);
    }
}


void deleteJobByID() {
    printf(CYAN "\n=== Delete Job (Admin) ===\n" RESET);
    int id;
    printf("Enter Job ID to delete: ");
    scanf("%d", &id);
    while(getchar()!='\n');

    Job* prev = NULL;
    Job* cur = jobList;
    while (cur) {
        if (cur->jobID == id) {
            if (prev) prev->next = cur->next;
            else jobList = cur->next;
            free(cur);

            // Also remove related applications
            Application* pa = NULL;
            Application* ca = applicationList;
            while (ca) {
                if (ca->jobID == id) {
                    Application* tofree = ca;
                    if (pa) pa->next = ca->next;
                    else applicationList = ca->next;
                    ca = ca->next;
                    free(tofree);
                } else {
                    pa = ca;
                    ca = ca->next;
                }
            }
            saveJobsToFile();
            saveApplicationsToFile();
            printf(GREEN "Job and all related applications have been removed.\n" RESET);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf(RED "Job ID not found.\n" RESET);
}