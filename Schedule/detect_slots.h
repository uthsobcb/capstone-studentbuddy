#ifndef DETECT_SLOTS_H
#define DETECT_SLOTS_H

#include "../global.h"
#include <stdio.h>
#include <string.h>

void detect_empty_slots(const char *account_number)
{
    struct Class account_classes[MAX_CLASSES];
    int account_class_count = 0;

    for (int i = 0; i < class_count; i++)
    {
        if (strcmp(classes[i].account_number, account_number) == 0)
        {
            account_classes[account_class_count++] = classes[i];
        }
    }

    if (account_class_count == 0)
    {
        printf("Your entire day is free.\n");
        return;
    }

    for (int i = 0; i < account_class_count - 1; i++)
    {
        for (int j = i + 1; j < account_class_count; j++)
        {
            if (account_classes[i].start_hour > account_classes[j].start_hour)
            {
                struct Class temp = account_classes[i];
                account_classes[i] = account_classes[j];
                account_classes[j] = temp;
            }
        }
    }

    printf("\n--- Empty Slots ---\n");
    int last_end = 0;
    for (int i = 0; i < account_class_count; i++)
    {
        if (account_classes[i].start_hour > last_end)
        {
            printf("Free: %02d:00 - %02d:00\n", last_end, account_classes[i].start_hour);
        }
        last_end = account_classes[i].end_hour;
    }

    if (last_end < 24)
    {
        printf("Free: %02d:00 - %02d:00\n", last_end, 24);
    }
}

#endif
