#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* structure definitions */
struct queue {
    int read;
    int write;
    int size;
    int *buffer;
};

struct packet {
    int arrival_time;
    int processing_time;
};

/* function prototypes */
void enqueue(struct queue *, int);
int dequeue(struct queue *);
bool is_empty(struct queue *);
bool is_full(struct queue *);

int main(void)
{
    int S, n;
    scanf("%d %d", &S, &n);

    /*
     * create queue data structure 
     * +1 is for extra buffer for preventing read == write when there are still elements 
     */
    int *buffer = malloc(sizeof(int) * (S + 1));
    struct queue *q = malloc(sizeof(struct queue));
    q->read = 0;
    q->write = 0;
    q->size = S;
    q->buffer = buffer;

    enqueue(q, 1);
    enqueue(q, 2);
    printf("%b\n", is_empty(q));
    enqueue(q, 3);
    dequeue(q);
    dequeue(q);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    enqueue(q, 7); //error
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    printf("%b\n", is_empty(q));
    
    

    free(q);
    free(buffer);
    return 0;
}

void enqueue(struct queue *q, int val)
{
    if (is_full(q)) {
        return;
    }
    q->buffer[q->write] = val;
    if (q->write == q->size) {
        q->write = 0; 
    } 
    else {
        (q->write)++;
    }
}

int dequeue(struct queue *q) {
    if (is_empty(q)) {
        return -1;
    }
    int r = q->buffer[q->read];
    if (q->read == q->size) {
        q->read = 0;
    } else {
        (q->read)++;
    }
    return r;
}

bool is_empty(struct queue *q)
{
    if (q->read == q->write) {
        return true;
    }
    return false;
}

bool is_full(struct queue *q)
{
    int num_elements = 0;
    if (q->write > q->read) {
        num_elements = q->write - q->read;
    } else if (q->write < q->read) {
        num_elements = (q->write + q->size + 1) - q->read;
    }
    if (num_elements == q->size) {
        return true;
    }
    return false;
}
