#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PRIME 1000000007
#define MULTIPLIER 263
#define MAX_BUFFER_LENGTH 40
#define MAX_NODE_DATA_LENGTH 40

struct node {
    char *data;
    struct node *prev;
    struct node *next;
};

struct query {
    char command[6];
    char string[16];
};

/* global values */
int BUCKET_NUM;
int N;
struct node **CHAINS;

/* function prototypes */
int poly_hash(char *S);
struct query *read_queries(void);
void process_queries(struct query *queries);
void read_globals(void);
void init_hash_table(void);
void free_memory(void);

int main(void)
{
    read_globals();
    init_hash_table();
    struct query *queries = read_queries();
    process_queries(queries);
    free_memory();
}

void read_globals(void)
{
    char buffer[MAX_BUFFER_LENGTH];
    fgets(buffer, MAX_BUFFER_LENGTH, stdin);
    sscanf(buffer, "%d", &BUCKET_NUM);
    fgets(buffer, MAX_BUFFER_LENGTH, stdin);
    sscanf(buffer, "%d", &N);
}

void init_hash_table(void)
{
    /* initialize the hash table with empty nodes */
    CHAINS = malloc(sizeof(struct node *) * BUCKET_NUM);
    for (int i = 0; i < BUCKET_NUM; ++i) {
        struct node *n = malloc(sizeof(struct node));
        n->data = NULL;
        n->prev = NULL;
        n->next = NULL;
        CHAINS[i] = n;
    }
}

struct query *read_queries(void)
{
    char buffer[MAX_BUFFER_LENGTH];
    struct query *queries = malloc(sizeof(struct query) * N);
    for (int i = 0; i < N; ++i) {
        fgets(buffer, MAX_BUFFER_LENGTH, stdin);
        /* delete the newline character at the end */
        int len = strlen(buffer);
        buffer[len - 1] = '\0';

        /* scan the buffer */
        struct query q;
        sscanf(buffer, "%s %s", &q.command, &q.string);
        queries[i] = q;
    }
    return queries;
}

void add(char *S)
{
    /* add a node to the chain along with the corresponding data. */
    int index = poly_hash(S);
    struct node *current = CHAINS[index];

    /* if the first position of chain is empty */
    if (current->data == NULL) {
        current->data = malloc(sizeof(char) * (strlen(S) + 1));
        strcpy(current->data, S);
        return;
    }
    /**
     * if the first node is full, iterate through the chain until finding 
     * a available location
     */
    while (current->data != NULL ) {
        /* if the data is in the current node, just do nothing */
        if (strcmp(current->data, S) == 0) {
            return;
        }
        /* break the look if it is end of the chain */
        if (current->next == NULL) {
            break;
        }
        current = current->next;
    }
    /**
     * allocate memory for a new node and the data of the node,
     * copy the string into the data part of the node
     * arrange, the next and prev pointers appropriately
     */
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = malloc(sizeof(char) * (strlen(S) + 1));
    strcpy(new_node->data, S);
    new_node->prev = current;
    new_node->next = NULL;
    current->next = new_node;
}

void del(char *S)
{
    /**
     * delete the corresponding node that includes the data, and arrange the relavant 
     * next and prev pointers of the node.
     */
    int index = poly_hash(S);
    struct node *current = CHAINS[index];
    /* the chain is empty */
    if (current->data == NULL) {
        return;
    }

    /* the first node matches */
    if (strcmp(current->data, S) == 0) {
        /* one node case */
        if (current->next == NULL) {
            current->data = NULL;
            return;
        } else {
            /* multiple node case */
            CHAINS[index] = current->next;
            current->next->prev = NULL;
            free(current->data);
            free(current);
            return;
        }
    }

    /* general case: iterate through to the chain for checking matching */
    while (current->next != NULL) {
        if (strcmp(current->next->data, S) == 0) {
            struct node *node_to_delete = current->next;
            current->next = node_to_delete->next;
            /* update the previos pointer of the next node */
            if (node_to_delete->next != NULL) {
                node_to_delete->next->prev = current;
            }
            free(node_to_delete->data);
            free(node_to_delete);
            return;
        }
        current = current->next;
    }
}

void find(char *S)
{
    /* prints yes, no, or newline based on the existence of the string */
    int index = poly_hash(S);
    struct node *current = CHAINS[index];
    
    /* the chain is empty */
    if (current->data == NULL) {
        printf("%s\n", "no");
        return;
    }

    while (current != NULL) {
        if (strcmp(current->data, S) == 0) {
            printf("%s\n", "yes");
            return;
        }
        current = current->next;
    }

    printf("%s\n", "no");
}

void check(char *S)
{
    /**
     * prints the data in the chain from tail to head, or newline character if the data is
     * not exist in the chain.
     */
    int index = atoi(S);
    struct node *current = CHAINS[index];
    if (current->next == NULL) {
        if (current->data == NULL) {
            printf("%c", '\n');
            return;
        }
        printf("%s\n", current->data);
        return;
    } 

    /* go to the last node of a chain */
    while (current->next != NULL) {
        current = current->next;
    }

    while (current->prev != NULL) {
        printf("%s ", current->data);
        current = current->prev;
    }
    printf("%s\n", current->data);
}

void process_queries(struct query *queries)
{
    for (int i = 0; i < N; ++i) {
        struct query q = queries[i];
        if (strcmp(q.command, "add") == 0) {
            add(q.string);
        } else if (strcmp(q.command, "del") == 0) {
            del(q.string);
        } else if (strcmp(q.command, "find") == 0) {
            find(q.string);
        } else if (strcmp(q.command, "check") == 0) {
            check(q.string);
        } else {
            printf("%s\n", "wrong command");
            exit(1);
        }
    }
}

int poly_hash(char *S)
{
    /* polynomial hash function, return the hash value of the string */
    long long int hash = 0;
    for (int i = strlen(S) - 1; i >= 0; i--) {
        hash = (hash * MULTIPLIER + S[i]) % PRIME;
    }
    hash = hash % BUCKET_NUM;
    return (int)hash;
}

void free_memory(void)
{
    /* frees the allocated memory places */
    for (int i = 0; i <BUCKET_NUM; ++i) {
        struct node *current = CHAINS[i];
        if (current->next == NULL) {
            free(current->data);
            free(current);
            continue;
        }
        while (current->next != NULL) {
            struct node *next_node = current->next;
            free(current->data);
            free(current);
            current = next_node;
        }
        CHAINS[i] = NULL;
    }
}
