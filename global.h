#ifndef GLOBAL_H
#define GLOBAL_H

#define USER "users.txt"
#define FILENAME "note_db.txt"

#define MAX_USERS 100
#define MAX_NOTES 100
#define MAX_LENGTH 100
#define ACCOUNT_NUMBER_LENGTH 6
#define USER "users.txt"

struct Note
{
    int id;
    char course[MAX_LENGTH];
    char date[11];
    char data[MAX_LENGTH];
    char tag[MAX_LENGTH];
    char account_number[ACCOUNT_NUMBER_LENGTH];
};

struct User
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char account_number[ACCOUNT_NUMBER_LENGTH];
};

extern struct Note notes[MAX_NOTES];
extern int note_count;

#endif
