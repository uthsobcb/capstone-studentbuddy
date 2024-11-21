#ifndef ADD_NOTE_H
#define ADD_NOTE_H

#include "../global.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int note_count;
struct Note notes[MAX_NOTES];

void get_current_date(char *date_str)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void add_note(const char *account_number)
{
    struct Note note;
    note.id = note_count + 1;

    printf("Enter course name: ");
    scanf(" %[^\n]", note.course);

    get_current_date(note.date);

    printf("Enter note data: ");
    scanf(" %[^\n]", note.data);

    printf("Enter tag: ");
    scanf("%s", note.tag);

    strncpy(note.account_number, account_number, sizeof(note.account_number) - 1);
    note.account_number[sizeof(note.account_number) - 1] = '\0';

    FILE *file = fopen(FILENAME, "a");
    if (!file)
    {
        perror("Failed to open notes database");
        return;
    }

    fprintf(file, "%d|%s|%s|%s|%s|%s\n",
            note.id,
            note.course,
            note.date,
            note.data,
            note.tag,
            note.account_number);
    fclose(file);

    notes[note_count++] = note;

    printf("Note added successfully!\n");
}

#endif
