#ifndef VIEW_SCHEDULE_H
#define VIEW_SCHEDULE_H

#include "../global.h"
#include <stdio.h>
#include <string.h>

void view_schedule(const char *account_number)
{
    int found = 0;

    printf("\n--- Your Class Schedule ---\n");
    for (int i = 0; i < class_count; i++)
    {
        if (strcmp(classes[i].account_number, account_number) == 0)
        {
            printf("%d. %s: %02d:00 - %02d:00\n",
                   classes[i].id,
                   classes[i].subject,
                   classes[i].start_hour,
                   classes[i].end_hour);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No classes found for your account.\n");
    }
}

#endif
