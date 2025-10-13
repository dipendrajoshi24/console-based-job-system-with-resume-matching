#ifndef JOB_MANAGEMENT_H
#define JOB_MANAGEMENT_H

#include "models.h"

Job* createJob(int jobID, const char* title, const char* company, const char* description, const char* requiredSkills, const char* requiredQualification, int priority);
void addJobInteractive();
void viewAllJobsInteractive();
void searchJobsInteractive();
void deleteJobByID();
void printJob(const Job* j);

#endif // JOB_MANAGEMENT_H