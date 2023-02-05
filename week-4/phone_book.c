#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 20 
#define MAX_BUFFER_LENGTH 100
#define CONTACT_LENGTH 10000000

/* function prototypes */
void find(char **contacts, char *phone_number);
void add(char **contacts, char *phone_number, char *name);
void delete(char **contacts, char *phone_number);
void process_queries(char **contacts);
char **init_contacts(void);

int main(void)
{
    char **contacts = init_contacts();
    process_queries(contacts);

    /* free allocated memory */
    for (int i = 0; i < CONTACT_LENGTH; ++i) {
       free(contacts[i]); 
    }
    free(contacts);
    return 0;
}

char **init_contacts(void)
{
    char **contacts = malloc(CONTACT_LENGTH * sizeof(char *));
    for (int i = 0; i < CONTACT_LENGTH; ++i) {
        contacts[i] = malloc(MAX_NAME_LENGTH * sizeof(char));
        strcpy(contacts[i], "not found");
    }
    return contacts;
}

void process_queries(char **contacts)
{
    int n;
    char buffer[MAX_BUFFER_LENGTH];
    fgets(buffer, MAX_BUFFER_LENGTH, stdin);
    n = atoi(buffer);
    for (int i = 0; i < n; ++i) {
        fgets(buffer, MAX_BUFFER_LENGTH, stdin);
        /* delete the newline character at the end */
        int len = strlen(buffer);
        buffer[len - 1] = '\0';
    
        char command[20];
        char number[20];
        char name[20];

        int num = sscanf(buffer, "%s %s %s", command, number, name);
        if (num == 3) {
            /* add command part */
            add(contacts, number, name);
        } else if (num == 2) {
            if (strcmp(command, "find") == 0) {
                find(contacts, number);
            } else if (strcmp(command, "del") == 0) {
                delete(contacts, number);
            }
        } else {
            printf("%s\n", "wrong input format");
            exit(1);
        }
    }
}

void add(char **contacts, char *phone_number, char *name)
{
    /* convert the phone number to an integer index */
    int num = atoi(phone_number);
    /* copy the name to the contacts array at the specified index (num) */
    strcpy(contacts[num], name);
}

void find(char **contacts, char *phone_number)
{
    /* convert the phone number to an integer index */
    int num = atoi(phone_number);
    /* print the contact name */
    printf("%s\n", contacts[num]);
}

void delete(char **contacts, char *phone_number)
{
    /* convert the phone number to an integer index */
    int num = atoi(phone_number);
    /* "delete" the contact by making it "not found" */
    strcpy(contacts[num], "not found");
}
