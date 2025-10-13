#include "user_management.h"
#include "file_handler.h"
#include "utils.h"

User* createUser(const char* name, const char* email, const char* password, const char* contact, const char* skills, const char* qualification, const char* cvLink, const char* role) {
    User* u = (User*)malloc(sizeof(User));
    if (!u) {
        perror("Failed to allocate memory for User");
        exit(EXIT_FAILURE);
    }
    strncpy(u->name, name, sizeof(u->name)-1); u->name[sizeof(u->name)-1] = '\0';
    strncpy(u->email, email, sizeof(u->email)-1); u->email[sizeof(u->email)-1] = '\0';
    strncpy(u->password, password, sizeof(u->password)-1); u->password[sizeof(u->password)-1] = '\0';
    strncpy(u->contact, contact, sizeof(u->contact)-1); u->contact[sizeof(u->contact)-1] = '\0';
    strncpy(u->skills, skills, sizeof(u->skills)-1); u->skills[sizeof(u->skills)-1] = '\0';
    strncpy(u->qualification, qualification, sizeof(u->qualification)-1); u->qualification[sizeof(u->qualification)-1] = '\0';
    strncpy(u->cvLink, cvLink, sizeof(u->cvLink)-1); u->cvLink[sizeof(u->cvLink)-1] = '\0';
    strncpy(u->role, role, sizeof(u->role)-1); u->role[sizeof(u->role)-1] = '\0';
    
    u->next = userList;
    userList = u;
    return u;
}

int emailExists(const char* email) {
    User* t = userList;
    while (t) {
        if (strcmp(t->email, email) == 0) return 1;
        t = t->next;
    }
    return 0;
}

void registerUserInteractive() {
    char name[64], email[64], password[32], contact[24], skills[256], qualification[64], cvLink[256];
    printf(CYAN "\n=== Register New User ===\n" RESET);
    printf("Full name: "); inputLine(name, sizeof(name)); trim(name);
    printf("Email (unique): "); inputLine(email, sizeof(email)); trim(email);
    if (emailExists(email)) {
        printf(RED "Error: email already registered. Please login.\n" RESET);
        return;
    }
    printf("Password: "); inputLine(password, sizeof(password));
    printf("Contact: "); inputLine(contact, sizeof(contact));
    printf("Skills (comma-separated): "); inputLine(skills, sizeof(skills));
    printf("Qualification: "); inputLine(qualification, sizeof(qualification));
    printf("CV Link / Path: "); inputLine(cvLink, sizeof(cvLink));
    
    createUser(name, email, password, contact, skills, qualification, cvLink, "user");
    saveUsersToFile();
    printf(GREEN "Registration successful. You can now login.\n" RESET);
}

int loginInteractive(int isAdminLogin) {
    char email[64], password[32];
    printf(CYAN "\n=== Login ===\n" RESET);
    printf("Email: "); inputLine(email, sizeof(email)); trim(email);
    printf("Password: "); inputLine(password, sizeof(password));

    User* t = userList;
    while (t) {
        if (strcmp(t->email, email) == 0 && strcmp(t->password, password) == 0) {
            if (isAdminLogin && strcmp(t->role, "admin") != 0) {
                printf(RED "Error: You are not an admin. Please use User Login.\n" RESET);
                return 0;
            }
            if (!isAdminLogin && strcmp(t->role, "user") != 0) {
                printf(RED "Error: Admins must use Admin Login.\n" RESET);
                return 0;
            }
            loggedInUser = t;
            printf(GREEN "Login successful. Welcome, %s!\n" RESET, t->name);
            return 1;
        }
        t = t->next;
    }
    printf(RED "Invalid credentials.\n" RESET);
    return 0;
}

void editProfile() {
    if (!loggedInUser) return;
    char buf[512];
    printf(CYAN "\n=== Edit Profile ===\n" RESET);
    printf("Current name: %s\n", loggedInUser->name);
    printf("New name (leave blank to keep): "); inputLine(buf, sizeof(buf)); trim(buf);
    if (strlen(buf)) strncpy(loggedInUser->name, buf, sizeof(loggedInUser->name)-1);

    printf("Current contact: %s\n", loggedInUser->contact);
    printf("New contact (leave blank to keep): "); inputLine(buf, sizeof(buf)); trim(buf);
    if (strlen(buf)) strncpy(loggedInUser->contact, buf, sizeof(loggedInUser->contact)-1);

    printf("Current skills: %s\n", loggedInUser->skills);
    printf("New skills (comma separated, leave blank to keep): "); inputLine(buf, sizeof(buf)); trim(buf);
    if (strlen(buf)) strncpy(loggedInUser->skills, buf, sizeof(loggedInUser->skills)-1);

    printf("Current qualification: %s\n", loggedInUser->qualification);
    printf("New qualification (leave blank to keep): "); inputLine(buf, sizeof(buf)); trim(buf);
    if (strlen(buf)) strncpy(loggedInUser->qualification, buf, sizeof(loggedInUser->qualification)-1);

    printf("CV Link: %s\nNew CV Link (leave blank to keep): ", loggedInUser->cvLink); inputLine(buf, sizeof(buf)); trim(buf);
    if (strlen(buf)) strncpy(loggedInUser->cvLink, buf, sizeof(loggedInUser->cvLink)-1);

    saveUsersToFile();
    printf(GREEN "Profile updated.\n" RESET);
}

void changePassword() {
    if (!loggedInUser) return;
    char oldp[64], newp[64];
    printf(CYAN "\n=== Change Password ===\n" RESET);
    printf("Old password: "); inputLine(oldp, sizeof(oldp));
    if (strcmp(oldp, loggedInUser->password) != 0) {
        printf(RED "Old password incorrect.\n" RESET);
        return;
    }
    printf("New password: "); inputLine(newp, sizeof(newp));
    strncpy(loggedInUser->password, newp, sizeof(loggedInUser->password)-1);
    saveUsersToFile();
    printf(GREEN "Password changed.\n" RESET);
}

void ensureDefaultAdmin() {
    User* t = userList;
    while (t) {
        if (strcmp(t->role, "admin") == 0) return;
        t = t->next;
    }
    createUser("Administrator", "admin@system.com", "admin", "N/A", "N/A", "N/A", "N/A", "admin");
    saveUsersToFile();
}