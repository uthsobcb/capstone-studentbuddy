#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Note/add_note.h"
#include "Note/load_note.h"
#include "Note/list_note.h"
#include "Note/edit.h"
#include "Note/delete.h"
#include "global.h"

#include "Schedule/schedule_db.h"
#include "Schedule/add_class.h"
#include "Schedule/view_schedule.h"
#include "Schedule/delete_class.h"
#include "Schedule/detect_slots.h"

typedef struct
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char account_number[ACCOUNT_NUMBER_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void load_users();
void save_users();
int find_user(const char *username);
void generate_account_number(char *account_number);
void register_user();
int login_user(char *username);

void load_users()
{
    FILE *file = fopen(USER, "r");
    if (file == NULL)
        return;

    while (fscanf(file, "%s %s %s", users[user_count].username, users[user_count].password, users[user_count].account_number) != EOF)
    {
        user_count++;
    }
    fclose(file);
}

void save_users()
{
    FILE *file = fopen(USER, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    for (int i = 0; i < user_count; i++)
    {
        fprintf(file, "%s %s %s\n", users[i].username, users[i].password, users[i].account_number);
    }
    fclose(file);
}

int find_user(const char *username)
{
    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            return i;
        }
    }
    return -1;
}

void generate_account_number(char *account_number)
{
    int number;
    int unique;

    srand(time(NULL));

    do
    {
        unique = 1;
        number = rand() % 10000;

        snprintf(account_number, ACCOUNT_NUMBER_LENGTH, "%04d", number);

        for (int i = 0; i < user_count; i++)
        {
            if (strcmp(users[i].account_number, account_number) == 0)
            {
                unique = 0;
                break;
            }
        }
    } while (!unique);
}

void register_user()
{
    char username[MAX_LENGTH], password[MAX_LENGTH];
    char account_number[ACCOUNT_NUMBER_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    if (find_user(username) != -1)
    {
        printf("\033[31m");
        printf("Username already exists.\n");
        printf("\033[0m");

        return;
    }

    printf("Enter password: ");
    scanf("%s", password);

    generate_account_number(account_number);

    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    strcpy(users[user_count].account_number, account_number);
    user_count++;

    save_users();

    printf("\033[32m");
    printf("Registration successful. Your account number is %s\n", account_number);
    printf("\033[0m");
}

int login_user(char *username)
{
    char password[MAX_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    int index = find_user(username);
    if (index == -1)
    {
        printf("Username not found.\n");
        return -1;
    }

    printf("Enter password: ");
    scanf("%s", password);
    if (strcmp(users[index].password, password) != 0)
    {
        printf("Incorrect password.\n");
        return -1;
    }

    return index;
}

void NoteManager(int logged_in_index)
{
    while (1)
    {
        int choice;
        printf("\nNote Manager:\n");
        printf("1. Add Note\n");
        printf("2. List Notes\n");
        printf("3. Edit Note\n");
        printf("4. Delete Note\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_note(users[logged_in_index].account_number);
            break;
        case 2:
            list_notes(users[logged_in_index].account_number);
            break;
        case 3:
            edit_note(users[logged_in_index].account_number);
            break;
        case 4:
            delete_note(users[logged_in_index].account_number);
            break;
        case 5:
            printf("Logging out...\n");
            logged_in_index = -1;
            return;
        default:
            printf("Invalid choice.\n");
        }
    }
}

void ScheduleManager(int logged_in_index)
{
    load_classes();

    while (1)
    {
        int choice;
        printf("\nSchedule Manager:\n");
        printf("1. Add Class\n");
        printf("2. View Schedule\n");
        printf("3. Delete Class\n");
        printf("4. Detect Empty Slots\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_class(users[logged_in_index].account_number);
            save_classes();
            break;
        case 2:
            view_schedule(users[logged_in_index].account_number);
            break;
        case 3:
            delete_class(users[logged_in_index].account_number);
            save_classes();
            break;
        case 4:
            detect_empty_slots(users[logged_in_index].account_number);
            break;
        case 5:
            printf("\033[31m");
            printf("Exiting Schedule Manager...\n");
            printf("\033[0m");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

int main()
{
    int choice;
    char username[MAX_LENGTH];
    int logged_in_index = -1;

    load_users();
    load_notes();

    time_t t;
    time(&t);

    printf("\033[36m");
    printf("============================================\n");
    printf("Welcome to StudentBuddy\n");
    printf("Comprehensive Note and Schedule Manager\n");
    printf("============================================\n");
    printf("\033[0m");
    while (1)
    {
        if (logged_in_index == -1)
        {
            printf("\n1. Register\n2. Login\n3. Exit\nChoose an option: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                register_user();
                break;
            case 2:
                logged_in_index = login_user(username);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice.\n");
            }
        }
        else
        {
            printf("\033[35m");
            printf("\nWelcome %s [ID: %s]\n", users[logged_in_index].username, users[logged_in_index].account_number);
            printf("It's %s\n", ctime(&t));
            printf("======================================\n");
            printf("\033[0m");
            printf("1. Note Manager\n");
            printf("2. Schedule Manager\n");
            printf("3. Logout\n");
            printf("Choose an option: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                NoteManager(logged_in_index);
                break;
            case 2:
                ScheduleManager(logged_in_index);
                break;
            case 3:
                logged_in_index = -1;
                printf("\033[31m");
                printf("Logged out successfully.\n");
                printf("\033[0m");
                break;
            default:
                printf("Invalid choice.\n");
            }
        }
    }
    return 0;
}
