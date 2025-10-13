#ifndef APPLICATION_MANAGEMENT_H
#define APPLICATION_MANAGEMENT_H

#include "models.h"

Application* createApplication(int jobID, const char* jobTitle, const char* applicantName, const char* applicantEmail, const char* applicantQual, const char* applicantCV);
void viewApplicantsForJob();
void exportApplicationsCSV();
void viewMyApplications();
void applyForJobByID(int id);

#endif 