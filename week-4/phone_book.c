#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 16
#define MAX_BUFFER_LENGTH 100
#define CARDINALITY 10

struct pair {
    char name[MAX_NAME_LENGTH];
    char phone[40];
};

struct node {
    struct pair *data_pair;
    struct node *prev;
    struct node *next;
};

/* function prototypes */
long int poly_hash(char *, int, int);
struct node *init_hash_table(void);
void add(struct node *, char *, char *);
void delete(struct node *, char *);
void find(struct node *, char *);
void read_queries(struct node *);

int main(void)
{
    struct node *chains = init_hash_table();

    read_queries(chains);
    free(chains);
    return 0;
}

struct node *init_hash_table(void)
{
    struct node *chains = malloc(sizeof(struct node) * CARDINALITY);
    for (int i = 0; i < CARDINALITY; ++i) {
        chains[i].data_pair = NULL;
        chains[i].prev = NULL;
        chains[i].next = NULL;
    }
    return chains;
}

void read_queries(struct node *chains)
{
    int n;
    char buffer[MAX_BUFFER_LENGTH];
    fgets(buffer, 4, stdin);
    n = atoi(buffer);
    for (int i = 0; i < n; ++i) {
        fgets(buffer, MAX_BUFFER_LENGTH, stdin);
        /* delete the newline character at the end */
        int len = strlen(buffer);
        buffer[len - 1] = '\0';
    
        char command[10];
        char number[20];
        char name[20];

        int num = sscanf(buffer, "%s %s %s", command, number, name);
        if (num == 3) {
            /* add command part */
            add(chains, number, name);
        } else if (num == 2) {
            if (strcmp(command, "find") == 0) {
                find(chains, number);
            } else if (strcmp(command, "del") == 0) {
                delete(chains, number);
            }
        } else {
            printf("%s\n", "wrong input format");
        }
    }
}

void find(struct node *chains, char *phone_number)
{
    long int index = poly_hash(phone_number, CARDINALITY, 13);
    struct node *first_node = &chains[index];
    if (first_node->next == NULL) {
        if (first_node->data_pair == NULL) {
            printf("%s\n", "not found");
            return;
        } 
        if (strcmp(first_node->data_pair->phone, phone_number) == 0) {
            printf("%s\n", first_node->data_pair->name);
        } else {
            printf("%s\n", "not found");
        }
        return;
    }
    struct node *current = first_node;
    while (current->next != NULL) {
        if (strcmp(current->data_pair->phone, phone_number) == 0) {
            printf("%s\n", current->data_pair->name);
        }
        current = current->next;
    }
    printf("%s\n", "not found");
}

void add(struct node *chains, char *phone_number, char *name)
{
    long int index = poly_hash(phone_number, CARDINALITY, 13);
    if (chains[index].data_pair == NULL) {
        struct pair *p = malloc(sizeof(struct pair));
        strcpy(p->name, name);
        strcpy(p->phone, phone_number);
        chains[index].data_pair = p;
        return;
    } else {
        struct node *current = &chains[index];
        while (current->next != NULL) {
            current = current->next;
        }
        struct node *new_node = malloc(sizeof(struct node));
        new_node->data_pair = malloc(sizeof(struct pair));
        strcpy(new_node->data_pair->name, name);
        strcpy(new_node->data_pair->phone, phone_number);
        new_node->prev = current;
        new_node->next = NULL;
        current->next = new_node;
    }
}

void delete(struct node *chains, char *phone_number)
{
    long int index = poly_hash(phone_number, CARDINALITY, 13);
    struct node *first_node = &chains[index];
    if (first_node->next == NULL) {
        if (first_node->data_pair == NULL) {
            return;
        } else {
            first_node->data_pair = NULL;
            return;
        }
    }

    struct node *current = first_node;
    while (current->next != NULL) {
        /* check if the current node contains the phone number to be deleted */
        if (strcmp(current->data_pair->phone, phone_number) == 0) {
            /* change the next and prev pointers accordingly*/
            struct node *previous_node = current->prev;
            previous_node->next = current->next;
            struct node *next_node = current->next;
            next_node->prev = current->prev;
            /* free the allocated memory of the current node*/
            free(current->data_pair);
            free(current);
            return;
        }
        current = current->next;
    }
}

long int poly_hash(char *S, int p, int x)
{
    long int hash = 0;
    for (int i = strlen(S) - 1; i >= 0; i--) {
        hash = (hash * x + S[i]) % p;
    }
    return hash;
}
