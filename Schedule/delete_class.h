#ifndef DELETE_CLASS_H
#define DELETE_CLASS_H

#include "../global.h"
#include "schedule_db.h"
#include <stdio.h>
#include <string.h>

void delete_class(const char *account_number)
{
    int id_to_delete;
    int found = 0;

    view_schedule(account_number);

    printf("Enter the class ID to delete: ");
    scanf("%d", &id_to_delete);

    for (int i = 0; i < class_count; i++)
    {
        if (classes[i].id == id_to_delete && strcmp(classes[i].account_number, account_number) == 0)
        {
            found = 1;

            for (int j = i; j < class_count - 1; j++)
            {
                classes[j] = classes[j + 1];
            }
            class_count--;
            break;
        }
    }

    if (found)
    {
        printf("Class deleted successfully!\n");
    }
    else
    {
        printf("Class ID not found or does not belong to your account.\n");
    }
}

#endif
