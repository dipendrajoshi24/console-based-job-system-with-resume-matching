#include "file_handler.h"
#include "user_management.h"
#include "job_management.h"
#include "application_management.h"
#include "utils.h"

void loadUsersFromFile() {
    FILE* f = fopen(USERS_FILE, "r");
    if (!f) return;
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        trim(line);
        if (strlen(line) == 0) continue;
        char name[64], email[64], password[32], contact[24], skills[256], qualification[64], cvLink[256], role[12];
        if (sscanf(line, "%63[^|]|%63[^|]|%31[^|]|%23[^|]|%255[^|]|%63[^|]|%255[^|]|%11[^\n]",
                   name, email, password, contact, skills, qualification, cvLink, role) == 8) {
            createUser(name, email, password, contact, skills, qualification, cvLink, role);
        }
    }
    fclose(f);
}

void saveUsersToFile() {
    FILE* f = fopen(USERS_FILE, "w");
    if (!f) {
        printf(RED "Error: cannot open users file for writing.\n" RESET);
        return;
    }
    User* t = userList;
    while (t) {
        fprintf(f, "%s|%s|%s|%s|%s|%s|%s|%s\n", t->name, t->email, t->password, t->contact, t->skills, t->qualification, t->cvLink, t->role);
        t = t->next;
    }
    fclose(f);
}

void loadJobsFromFile() {
    FILE* f = fopen(JOBS_FILE, "r");
    if (!f) return;
    char line[1200];
    while (fgets(line, sizeof(line), f)) {
        trim(line);
        if (strlen(line) == 0) continue;
        int jobID = 0, priority = 0;
        char title[128], company[64], description[512], requiredSkills[256], requiredQualification[64];
        if (sscanf(line, "%d|%127[^|]|%63[^|]|%511[^|]|%255[^|]|%63[^|]|%d",
                   &jobID, title, company, description, requiredSkills, requiredQualification, &priority) == 7) {
            createJob(jobID, title, company, description, requiredSkills, requiredQualification, priority);
        }
    }
    fclose(f);
}

void saveJobsToFile() {
    FILE* f = fopen(JOBS_FILE, "w");
    if (!f) {
        printf(RED "Error: cannot open jobs file for writing.\n" RESET);
        return;
    }
    Job* t = jobList;
    while (t) {
        fprintf(f, "%d|%s|%s|%s|%s|%s|%d\n",
                t->jobID, t->title, t->company, t->description, t->requiredSkills, t->requiredQualification, t->priority);
        t = t->next;
    }
    fclose(f);
}

void loadApplicationsFromFile() {
    FILE* f = fopen(APPS_FILE, "r");
    if (!f) return;
    char line[1024];
    // Skip header line if it exists
    fgets(line, sizeof(line), f); 
    while (fgets(line, sizeof(line), f)) {
        trim(line);
        if (strlen(line) == 0) continue;
        int jobID;
        char jobTitle[128], applicantName[64], applicantEmail[64], applicantQualification[64], applicantCV[256];
        if (sscanf(line, "%d,%127[^,],%63[^,],%63[^,],%63[^,],%255[^\n]",
                   &jobID, jobTitle, applicantName, applicantEmail, applicantQualification, applicantCV) == 6) {
            createApplication(jobID, jobTitle, applicantName, applicantEmail, applicantQualification, applicantCV);
        }
    }
    fclose(f);
}

void saveApplicationsToFile() {
    FILE* f = fopen(APPS_FILE, "w");
    if (!f) {
        printf(RED "Error: cannot open applications file for writing.\n" RESET);
        return;
    }
    // Add a header row for clarity
    fprintf(f, "JobID,JobTitle,ApplicantName,ApplicantEmail,ApplicantQualification,CVLink\n");
    Application* t = applicationList;
    while (t) {
        fprintf(f, "%d,%s,%s,%s,%s,%s\n",
                t->jobID, t->jobTitle, t->applicantName, t->applicantEmail, t->applicantQualification, t->applicantCV);
        t = t->next;
    }
    fclose(f);
}

void loadAll() {
    loadUsersFromFile();
    loadJobsFromFile();
    loadApplicationsFromFile();
}

void saveAll() {
    saveUsersToFile();
    saveJobsToFile();
    saveApplicationsToFile();
}