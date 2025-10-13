#include "utils.h"

void inputLine(char* buffer, int size) {
    if (!fgets(buffer, size, stdin)) {
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

void trim(char* s) {
    char* start = s;
    while (isspace((unsigned char)*start)) {
        start++;
    }
    char* end = s + strlen(s) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';
    if (start != s) {
        memmove(s, start, strlen(start) + 1);
    }
}

void toLowerCase(char* s) {
    for (int i = 0; s[i]; i++) {
        s[i] = (char)tolower((unsigned char)s[i]);
    }
}

int matchPercentage(const char* userSkills, const char* jobSkills, const char* userQual, const char* jobQual) {
    if (!jobSkills) return 0;

    char uSkills[512], jSkills[512];
    strncpy(uSkills, userSkills ? userSkills : "", sizeof(uSkills)-1);
    uSkills[sizeof(uSkills)-1] = '\0';
    strncpy(jSkills, jobSkills ? jobSkills : "", sizeof(jSkills)-1);
    jSkills[sizeof(jSkills)-1] = '\0';

    toLowerCase(uSkills);
    toLowerCase(jSkills);
    trim(uSkills);
    trim(jSkills);

    int totalJobSkills = 0;
    if (strlen(jSkills) > 0) {
        totalJobSkills = 1;
        for (int i = 0; jSkills[i]; i++) {
            if (jSkills[i] == ',') totalJobSkills++;
        }
    }

    if (totalJobSkills == 0) return 100; // Or 0, depending on logic for no required skills

    int matched = 0;
    char* jSkillsCopy = strdup(jSkills); // Use a copy for strtok
    char* p = strtok(jSkillsCopy, ",");
    while (p) {
        trim(p);
        if (strlen(p) > 0 && strstr(uSkills, p) != NULL) {
            matched++;
        }
        p = strtok(NULL, ",");
    }
    free(jSkillsCopy);

    double skillScore = (double)matched / (double)totalJobSkills;

    int qualMatch = 0;
    if (jobQual && strlen(jobQual) > 0 && userQual && strlen(userQual) > 0) {
        char uq[128], jq[128];
        strncpy(uq, userQual, sizeof(uq)-1); uq[sizeof(uq)-1] = '\0';
        strncpy(jq, jobQual, sizeof(jq)-1); jq[sizeof(jq)-1] = '\0';
        toLowerCase(uq); toLowerCase(jq);
        trim(uq); trim(jq);
        if (strstr(uq, jq) != NULL || strstr(jq, uq) != NULL) {
            qualMatch = 1;
        }
    } else if (!jobQual || strlen(jobQual) == 0) {
        qualMatch = 1; // No qualification required, so it's a match
    }

    double score = skillScore * 0.7 + (qualMatch ? 0.3 : 0.0);
    int percent = (int)(score * 100.0 + 0.5);
    return percent > 100 ? 100 : percent;
}