#include <stdio.h>
#include <string.h>
#include "ai_logic.h"
#include "memory.h"

void toLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

int main() {
    char input[500];
    char name[200];

    /* -------- GREETING -------- */
    if (loadName(name))
        printf("AI: Welcome back, %s.\n", name);
    else
        printf("AI: Hello. I don't know your name yet.\n");

    /* -------- PERSONALITY SELECTION -------- */
    choosePersonality();
    printf("AI: Personality set. Let's continue.\n");

    /* -------- RUN SETUP ONLY IF NEW USER -------- */
    if (!loadName(name)) {
        initialSetup();
    }

    /* -------- MAIN LOOP -------- */
    while (1) {
        printf("You: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        toLowerCase(input);

        if (strcmp(input, "exit") == 0 || strcmp(input, "bye") == 0) {
            printf("AI: Goodbye.\n");
            break;
        }

        processInput(input);
    }

    return 0;
}
