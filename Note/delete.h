#ifndef DELETE_H
#define DELETE_H

#include "../global.h"
#include <stdio.h>
#include <string.h>

void delete_note(char *account_number)
{
    int id;
    printf("Enter the ID of the note you want to delete: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input. Please enter a valid ID.\n");
        return;
    }

    FILE *file = fopen(FILENAME, "r");
    FILE *temp_file = fopen("temp_db.txt", "w");

    if (!file || !temp_file)
    {
        perror("Failed to open files");
        if (file)
            fclose(file);
        if (temp_file)
            fclose(temp_file);
        return;
    }

    struct Note note;
    int found = 0;

    while (fscanf(file, "%d|%49[^|]|%10[^|]|%249[^|]|%19[^|]|%19[^\n]\n",
                  &note.id, note.course, note.date, note.data, note.tag, note.account_number) == 6)
    {
        if (note.id == id && strcmp(note.account_number, account_number) == 0)
        {
            found = 1;
            printf("Note with ID %d deleted successfully!\n", id);
            continue;
        }
        fprintf(temp_file, "%d|%s|%s|%s|%s|%s\n", note.id, note.course, note.date, note.data, note.tag, note.account_number);
    }

    fclose(file);
    fclose(temp_file);

    if (!found)
    {
        printf("Note with ID %d not found or it doesn't belong to your account.\n", id);
        remove("temp_db.txt");
    }
    else
    {
        int new_count = 0;
        for (int i = 0; i < note_count; i++)
        {
            if (notes[i].id != id || strcmp(notes[i].account_number, account_number) != 0)
            {
                notes[new_count++] = notes[i];
            }
        }
        note_count = new_count;

        remove(FILENAME);
        rename("temp_db.txt", FILENAME);
    }
}

#endif
