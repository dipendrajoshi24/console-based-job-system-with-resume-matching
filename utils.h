#ifndef UTILS_H
#define UTILS_H

#include "models.h"

void inputLine(char* buffer, int size);
void trim(char* s);
void toLowerCase(char* s);
int matchPercentage(const char* userSkills, const char* jobSkills, const char* userQual, const char* jobQual);

#endif // UTILS_H