#ifndef SCHEDULE_DB_H
#define SCHEDULE_DB_H

#include "../global.h"
#include <stdio.h>
#include <string.h>

int class_count = 0;
struct Class classes[MAX_CLASSES];

void load_classes()
{
    FILE *file = fopen(SCHEDULEDB, "r");
    if (!file)
    {
        printf("No schedule data found. Starting fresh...\n");
        return;
    }

    while (fscanf(file, "%d|%[^|]|%d|%d|%s\n",
                  &classes[class_count].id,
                  classes[class_count].subject,
                  &classes[class_count].start_hour,
                  &classes[class_count].end_hour,
                  classes[class_count].account_number) != EOF)
    {
        class_count++;
    }
    fclose(file);
}

void save_classes()
{
    FILE *file = fopen("schedule_db.txt", "w");
    if (!file)
    {
        perror("Failed to save schedule data");
        return;
    }

    for (int i = 0; i < class_count; i++)
    {
        fprintf(file, "%d|%s|%d|%d|%s\n",
                classes[i].id,
                classes[i].subject,
                classes[i].start_hour,
                classes[i].end_hour,
                classes[i].account_number);
    }
    fclose(file);
}

#endif
