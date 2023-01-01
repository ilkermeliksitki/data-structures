#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100000

/* structure definitions */
struct queue {
    int front;
    int rear;
    int elements[MAX_SIZE];
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
    
    return 0;
}

void enqueue(struct queue *q, int val)
{
    if (is_full(q)) {
        return;
    }
    q->elements[++(q->rear)] = val;
}

int dequeue(struct queue *q)
{
    if (is_full(q)) {
        return -1;
    }
    return q->elements[(q->front)++];
}

bool is_empty(struct queue *q)
{
    if (q->front == q->rear) {
        return true;
    }
    return false;
}

bool is_full(struct queue *q)
{
    if (q->rear == MAX_SIZE - 1) {
        return true;
    }
    return false;
}
