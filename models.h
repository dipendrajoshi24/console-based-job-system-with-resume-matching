#ifndef MODELS_H
#define MODELS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- ANSI Color Codes ---
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BOLD    "\x1b[1m"

// --- File Definitions ---
#define USERS_FILE "users.txt"
#define JOBS_FILE "jobs.txt"
#define APPS_FILE  "applications.csv"

// --- Data Structures ---
typedef struct User {
    char name[64];
    char email[64];
    char password[32];
    char contact[24];
    char skills[256];
    char qualification[64];
    char cvLink[256];
    char role[12];
    struct User* next;
} User;

typedef struct Job {
    int jobID;
    char title[128];
    char company[64];
    char description[512];
    char requiredSkills[256];
    char requiredQualification[64];
    int priority;
    struct Job* next;
} Job;

typedef struct Application {
    int jobID;
    char jobTitle[128];
    char applicantName[64];
    char applicantEmail[64];
    char applicantQualification[64];
    char applicantCV[256];
    struct Application* next;
} Application;

// --- Global Variables (declared as extern) ---
extern User* userList;
extern Job* jobList;
extern Application* applicationList;
extern User* loggedInUser;

#endif // MODELS_H