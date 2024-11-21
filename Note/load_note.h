#ifndef LOAD_NOTE_H
#define LOAD_NOTE_H

#include <stdio.h>
#include <string.h>
#include "../global.h"

void load_notes()
{
    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        perror("Failed to open notes database");
        return;
    }

    note_count = 0;
    struct Note note;

    while (fscanf(file, "%d|%49[^|]|%10[^|]|%249[^|]|%19[^|]|%19[^\n]\n",
                  &note.id, note.course, note.date, note.data, note.tag, note.account_number) == 6)
    {
        notes[note_count++] = note;
        if (note_count >= MAX_NOTES)
        {
            printf("Warning: Maximum note capacity reached. Some notes may not be loaded.\n");
            break;
        }
    }

    fclose(file);
    printf("%d notes loaded successfully.\n", note_count);
}

#endif
