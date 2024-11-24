#ifndef SAVE_NOTE_H
#define SAVE_NOTE_H

#include "../global.h"
#include <stdio.h>

void save_notes()
{
    if (note_count == 0)
    {
        printf("No notes to save.\n");
        return;
    }

    FILE *file = fopen(FILENAME, "w");
    if (!file)
    {
        perror("Failed to open notes database for writing");
        return;
    }

    for (int i = 0; i < note_count; i++)
    {
        if (fprintf(file, "%d|%s|%s|%s|%s|%s\n",
                    notes[i].id, notes[i].course, notes[i].date, notes[i].data, notes[i].tag, notes[i].account_number) < 0)
        {
            perror("Error writing to notes database");
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Notes saved successfully!\n");
}

#endif
