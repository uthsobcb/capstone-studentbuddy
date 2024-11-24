#ifndef ADD_CLASS_H
#define ADD_CLASS_H

#include "../global.h"
#include <stdio.h>
#include <string.h>

void add_class(const char *account_number)
{
    if (class_count >= MAX_CLASSES)
    {
        printf("Schedule is full. Cannot add more classes.\n");
        return;
    }

    struct Class new_class;
    new_class.id = class_count + 1;

    printf("Enter class subject: ");
    scanf(" %[^\n]", new_class.subject);

    printf("Enter start hour (24-hour format): ");
    scanf("%d", &new_class.start_hour);

    printf("Enter end hour (24-hour format): ");
    scanf("%d", &new_class.end_hour);

    strncpy(new_class.account_number, account_number, sizeof(new_class.account_number) - 1);
    new_class.account_number[sizeof(new_class.account_number) - 1] = '\0';

    classes[class_count++] = new_class;

    printf("Class added successfully!\n");
}

#endif
