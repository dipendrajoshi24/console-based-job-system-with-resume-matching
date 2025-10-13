#include "models.h"
#include "file_handler.h"
#include "user_management.h"
#include "ui.h"

User* userList = NULL;
Job* jobList = NULL;
Application* applicationList = NULL;
User* loggedInUser = NULL;

void freeAllMemory() {
    User* currentUser = userList;
    while (currentUser != NULL) {
        User* next = currentUser->next;
        free(currentUser);
        currentUser = next;
    }

    Job* currentJob = jobList;
    while (currentJob != NULL) {
        Job* next = currentJob->next;
        free(currentJob);
        currentJob = next;
    }

    Application* currentApp = applicationList;
    while (currentApp != NULL) {
        Application* next = currentApp->next;
        free(currentApp);
        currentApp = next;
    }
}

int main() {
    loadAll();
    
    ensureDefaultAdmin();

    mainMenuLoop();
    
    saveAll();
    printf(GREEN "\nAll data has been saved. Exiting... Goodbye!\n" RESET);

    freeAllMemory();
    
    return 0;
}