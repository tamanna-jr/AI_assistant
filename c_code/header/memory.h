#ifndef MEMORY_H
#define MEMORY_H

void saveName(char name[]);
int loadName(char name[]);

void savePreference(char key[], char value[]);
int loadPreference(char key[], char value[]);
void updatePreference(char key[], char value[]);

#endif
