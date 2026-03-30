#include <stdio.h>
#include <string.h>
#include "memory.h"

void saveName(char name[]) {
    FILE *file = fopen("name.txt", "w");
    if (!file) return;
    fprintf(file, "%s", name);
    fclose(file);
}

int loadName(char name[]) {
    FILE *file = fopen("name.txt", "r");
    if (!file) return 0;
    fgets(name, 500, file);
    name[strcspn(name, "\n")] = 0;
    fclose(file);
    return 1;
}

/* Overwrites existing key */
void updatePreference(char key[], char value[]) {
    FILE *file = fopen("profile.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    char line[600], k[100], v[500];
    int found = 0;

    if (file) {
        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "%[^=]=%[^\n]", k, v) != 2)
                continue;

            if (strcmp(k, key) == 0) {
                fprintf(temp, "%s=%s\n", key, value);
                found = 1;
            } else {
                fprintf(temp, "%s", line);
            }
        }
        fclose(file);
    }

    if (!found) {
        fprintf(temp, "%s=%s\n", key, value);
    }

    fclose(temp);

    remove("profile.txt");
    rename("temp.txt", "profile.txt");
}

void savePreference(char key[], char value[]) {
    updatePreference(key, value);
}

int loadPreference(char key[], char value[]) {
    FILE *file = fopen("profile.txt", "r");
    char line[600], k[100], v[500];

    if (!file) return 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^=]=%[^\n]", k, v) != 2)
            continue;

        if (strcmp(k, key) == 0) {
            strcpy(value, v);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
