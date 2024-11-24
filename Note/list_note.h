#ifndef LIST_NOTES_H
#define LIST_NOTES_H

#include "../global.h"
#include <stdio.h>
#include <string.h>

void list_notes(char *account_number)
{
    int displayed_count = 0;

    if (note_count == 0)
    {
        printf("No notes available.\n");
        return;
    }

    printf("Listing notes for account: %s\n", account_number);
    printf("\033[35m");

    printf("========================================\n");

    for (int i = 0; i < note_count; i++)
    {
        if (strcmp(notes[i].account_number, account_number) == 0)
        {
            printf("ID: %d\n", notes[i].id);
            printf("Course: %s\n", notes[i].course);
            printf("Date: %s\n", notes[i].date);
            printf("Note: %s\n", notes[i].data);
            printf("Tag: %s\n", notes[i].tag);
            printf("========================================\n");
            displayed_count++;
        }
    }
    printf("\033[0m");

    if (displayed_count == 0)
    {
        printf("No notes found for this account.\n");
    }
}

#endif
