#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include "models.h"

User* createUser(const char* name, const char* email, const char* password, const char* contact, const char* skills, const char* qualification, const char* cvLink, const char* role);
void registerUserInteractive();
int loginInteractive(int isAdminLogin);
void editProfile();
void changePassword();
void ensureDefaultAdmin();
int emailExists(const char* email);

#endif // USER_MANAGEMENT_H