#ifndef EDIT_H
#define EDIT_H

#include "./global.h"
#include "save_note.h"
#include <stdio.h>
#include <string.h>

void edit_note(char *account_number)
{
    int id;
    printf("Enter the ID of the note you want to edit: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input. Please enter a valid ID.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < note_count; i++)
    {
        // Check if the note belongs to the authenticated user
        if (notes[i].id == id && strcmp(notes[i].account_number, account_number) == 0)
        {
            found = 1;
            printf("\nEditing Note ID: %d\n", id);

            // Edit Course
            printf("Current Course: %s\n", notes[i].course);
            printf("Enter new Course (or press Enter to keep current): ");
            char course[100];
            fgets(course, sizeof(course), stdin); // Use fgets for better input handling
            if (strlen(course) > 1)               // Check if input is not just Enter
            {
                course[strcspn(course, "\n")] = '\0'; // Remove trailing newline
                strncpy(notes[i].course, course, sizeof(notes[i].course) - 1);
                notes[i].course[sizeof(notes[i].course) - 1] = '\0';
            }

            // Edit Date
            printf("Current Date: %s\n", notes[i].date);
            printf("Enter new Date (YYYY-MM-DD) (or press Enter to keep current): ");
            char date[20];
            fgets(date, sizeof(date), stdin);
            if (strlen(date) > 1)
            {
                date[strcspn(date, "\n")] = '\0';
                strncpy(notes[i].date, date, sizeof(notes[i].date) - 1);
                notes[i].date[sizeof(notes[i].date) - 1] = '\0';
            }

            // Edit Note Data
            printf("Current Note Data: %s\n", notes[i].data);
            printf("Enter new Note Data (or press Enter to keep current): ");
            char data[1000];
            fgets(data, sizeof(data), stdin);
            if (strlen(data) > 1)
            {
                data[strcspn(data, "\n")] = '\0';
                strncpy(notes[i].data, data, sizeof(notes[i].data) - 1);
                notes[i].data[sizeof(notes[i].data) - 1] = '\0';
            }

            // Edit Tag
            printf("Current Tag: %s\n", notes[i].tag);
            printf("Enter new Tag (or press Enter to keep current): ");
            char tag[50];
            fgets(tag, sizeof(tag), stdin);
            if (strlen(tag) > 1)
            {
                tag[strcspn(tag, "\n")] = '\0';
                strncpy(notes[i].tag, tag, sizeof(notes[i].tag) - 1);
                notes[i].tag[sizeof(notes[i].tag) - 1] = '\0';
            }

            save_notes();
            printf("Note updated successfully!\n");
            break;
        }
    }

    if (!found)
    {
        printf("Note with ID %d not found or it doesn't belong to your account.\n", id);
    }
}

#endif
