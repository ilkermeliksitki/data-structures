#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* structure definitions */
struct queue {
    int read;
    int write;
    int size;
    struct packet *buffer;
};

struct packet {
    int arrival_time;
    int processing_time;
    int error_val;
};

/* function prototypes */
void enqueue(struct queue *, struct packet);
struct packet dequeue(struct queue *);
bool is_empty(struct queue *);
bool is_full(struct queue *);

int main(void)
{
    int S, n;
    scanf("%d %d", &S, &n);

    /* create queue data structure 
     * +1 is for extra buffer for preventing read == write when there are still elements 
     */
    struct packet *buffer = malloc(sizeof(struct packet) * (S + 1));
    struct queue *q = malloc(sizeof(struct queue));
    q->read = 0;
    q->write = 0;
    q->size = S;
    q->buffer = buffer;




    free(q);
    free(buffer);
    return 0;
}

void enqueue(struct queue *q, struct packet val)
{
    /* enqueue function works by a circular fashion.
     * after getting the limit of allocated array, the index wraps around and starts
     * from 0, if there is enough space for adding a new element to queue.
     */
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

struct packet dequeue(struct queue *q) {
    if (is_empty(q)) {
        struct packet p;
        p.error_val = -1;
        return p;
    }
    struct packet r = q->buffer[q->read];
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
    /* is_full function checks the number of elements by using write and read index.
     * if number of elements is equal to queue limit, it returs true, and vice versa.
     */
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
