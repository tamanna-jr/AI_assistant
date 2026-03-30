# AI_assistant

A console-based chatbot developed in C that simulates interactive conversation using personality-driven responses, persistent memory, and structured user interaction.

---

## Overview

This project implements a rule-based conversational assistant that adapts its responses based on user-selected personalities and retains user-specific data across sessions using file handling.

The system demonstrates how low-level programming in C can be used to build a stateful and interactive application.

---

## Core Features

### Personality System
- Supports three modes: **Friendly**, **Sarcastic**, and **Neutral**
- Response tone adapts dynamically based on the selected personality
- Personality can be changed at any time during execution

### Persistent Memory
- Stores user data using file handling:
  - Name
  - Likes
  - Dislikes
  - Interests
- Data persists across multiple program runs
- Supports updating and overwriting stored values

### Interactive Onboarding
- Collects user information during initial setup
- Ensures a personalized experience from the first interaction

### Context Awareness
- Maintains short-term conversational context
- Can recall previously provided information when prompted

### Conversational Handling
Supports structured interaction for:
- Greetings (e.g., "good morning", "good night")
- Gratitude (e.g., "thank you", "thanks")
- General queries (e.g., "who are you", "how are you")
- Informational queries (e.g., "what do you know about me")

### User Control
- Change personality during runtime
- Update personal data using natural input
- Retrieve stored data using simple queries

---


## Implementation Details

- Language: **C**
- Libraries used:
  - `stdio.h`
  - `string.h`
- Uses file handling for persistent storage
- Implements keyword-based input parsing using `strstr`
- Follows a modular design for clarity and scalability

---

## Execution Flow

1. Load stored user data (if available)  
2. Prompt user to select a personality  
3. Perform onboarding for new users  
4. Process input using rule-based matching  
5. Generate responses based on:
   - User input  
   - Stored data  
   - Selected personality  
6. Update stored information when required  

---

## Learning Outcomes

- Modular programming in C  
- File handling and persistent data storage  
- Basic natural language processing using string matching  
- Designing interactive and user-driven systems  

---

## Future Scope

- Support multiple values for preferences (e.g., multiple likes)
- Improve input parsing and intent detection
- Develop a graphical user interface
- Extend to voice-based interaction

---

## Summary

This project demonstrates the design and implementation of a structured conversational system in C, combining personality, memory, and interaction to create a functional and extensible chatbot.

---

## Resume Line

Developed a console-based AI chatbot in C featuring personality-driven responses and persistent memory using file handling, enabling interactive and stateful user communication.
