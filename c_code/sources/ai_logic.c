#include <stdio.h>
#include <string.h>
#include "memory.h"

char lastContext[200] = "";
char lastType[50] = "";

/* -------- RESPONSE SYSTEM -------- */
void respond(char message[], char type[]) {
    char style[100];

    if (loadPreference("personality", style)) {

        /* FRIENDLY */
        if (strcmp(style, "friendly") == 0) {
            if (strcmp(type, "greet") == 0)
                printf("AI: It's nice talking to you.\n");
            else if (strcmp(type, "status") == 0)
                printf("AI: I'm doing well. Thanks for asking.\n");
            else if (strcmp(type, "thanks") == 0)
                printf("AI: You're always welcome. Happy to help.\n");
            else
                printf("AI: %s\n", message);
        }

        /* SARCASTIC */
        else if (strcmp(style, "sarcastic") == 0) {
            if (strcmp(type, "greet") == 0)
                printf("AI: Oh, it's you again.\n");
            else if (strcmp(type, "status") == 0)
                printf("AI: I'm a program. I don't have feelings.\n");
            else if (strcmp(type, "thanks") == 0)
                printf("AI: That was expected.\n");
            else
                printf("AI: %s\n", message);
        }

        /* NEUTRAL */
        else {
            printf("AI: %s\n", message);
        }
    } else {
        printf("AI: %s\n", message);
    }
}

/* -------- PERSONALITY MENU -------- */
void choosePersonality() {
    char input[50];

    printf("AI: Choose a personality:\n");
    printf("1. Friendly\n2. Sarcastic\n3. Neutral\n");
    printf("Enter choice: ");

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "1") == 0)
        savePreference("personality", "friendly");
    else if (strcmp(input, "2") == 0)
        savePreference("personality", "sarcastic");
    else
        savePreference("personality", "neutral");

    printf("AI: Personality updated.\n");
}

/* -------- INITIAL SETUP -------- */
void initialSetup() {
    char input[200], name[200];

    printf("AI: I would like to know you better.\n");

    if (!loadName(name)) {
        printf("AI: What is your name?\nYou: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        saveName(name);
    }

    printf("AI: Tell me something you like:\nYou: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    savePreference("likes", input);

    printf("AI: Tell me something you dislike:\nYou: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    savePreference("dislikes", input);

    printf("AI: What are you interested in?\nYou: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    savePreference("interest", input);

    printf("AI: Thank you. I have saved your preferences.\n");
}

/* -------- MAIN LOGIC -------- */
void processInput(char input[]) {

    char value[200];

    /* -------- PERSONALITY CHANGE -------- */
    if (strstr(input, "change personality") || strstr(input, "switch personality")) {
        choosePersonality();
    }

    else if (strstr(input, "yes") && strstr(input, "personality")) {
        choosePersonality();
    }

    /* -------- NAME -------- */
    else if (strstr(input, "change my name to") || strstr(input, "set my name to") || strstr(input, "my new name is")) {
        char name[200];
        int offset = strstr(input, "change my name to") ? 18 : 15;

        strncpy(name, input + offset, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';

        saveName(name);
        strcpy(lastContext, name);
        strcpy(lastType, "name");

        printf("AI: I will call you %s from now on.\n", name);
    }

    else if (strstr(input, "what is my name")) {
        char name[200];
        if (loadName(name))
            printf("AI: Your name is %s.\n", name);
        else
            respond("I do not have your name yet.", "default");
    }

    /* -------- RECALL USER DATA -------- */
    else if (strstr(input, "what do you know about me")) {
        char name[200], like[200], dislike[200], interest[200];

        if (loadName(name))
            printf("AI: Your name is %s.\n", name);

        if (loadPreference("likes", like))
            printf("AI: You like %s.\n", like);

        if (loadPreference("dislikes", dislike))
            printf("AI: You dislike %s.\n", dislike);

        if (loadPreference("interest", interest))
            printf("AI: You are interested in %s.\n", interest);
    }

    /* -------- SIMPLE CONVERSATION -------- */
    else if (strstr(input, "how are you")) {
        respond("", "status");
    }

    else if (strstr(input, "who are you")) {
        printf("AI: I am a simple AI assistant built in C.\n");
    }

    else if (strstr(input, "what are you doing")) {
        printf("AI: I am assisting you.\n");
    }

    /* -------- SOCIAL -------- */
    else if (strstr(input, "thank you") || strstr(input, "thanks")) {
        respond("anytime!", "thanks");
    }

    else if (strstr(input, "good morning")) {
        respond("Good morning.", "greet");
    }

    else if (strstr(input, "good night")) {
        respond("Good night.", "greet");
    }

    else if (strstr(input, "congrats") || strstr(input, "congratulations")) {
        respond("Congratulations.", "default");
    }

    /* -------- CONTEXT -------- */
    else if (strstr(input, "tell me again")) {
        if (strlen(lastContext) > 0) {
            if (strcmp(lastType, "name") == 0)
                printf("AI: Your name is %s.\n", lastContext);
        } else {
            respond("No previous context found.", "default");
        }
    }

    /* -------- PROMPT PERSONALITY CHANGE -------- */
    else if (strstr(input, "bored") || strstr(input, "change something")) {
        printf("AI: Would you like to change the personality?\n");
    }

    /* -------- DEFAULT -------- */
    else {
        respond("I am still learning.", "default");
    }
}
