#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_DEQUEU_SIZE 10

struct deque {
    int front;
    int rear;
    int elements[MAX_DEQUEU_SIZE];
};

/* function prototypes */
void init_deque(struct deque *);
bool is_empty(struct deque *);
bool is_full(struct deque *);
void push_front(struct deque *, int);
void push_back(struct deque *, int);
int pop_front(struct deque *);
int pop_back(struct deque *);

void print_elements(struct deque *d)
{
    for (int i = 0; i < MAX_DEQUEU_SIZE; ++i) {
        printf("%d ", d->elements[i]);
    }
    printf("%c", '\n');
}

int main(void)
{
    /**
    int n;
    scanf("%d", &n);
    int nums[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &nums[i]);
    }
    int m;
    scanf("%d", &m);
    */
    struct deque *d = malloc(sizeof(struct deque));
    init_deque(d);
    push_back(d, 2);
    print_elements(d);
    push_front(d, 3);
    print_elements(d);
    push_front(d, 5);
    print_elements(d);
    print_elements(d);
    print_elements(d);
    return 0;
}

void init_deque(struct deque *d)
{
    d->front = 0;
    d->rear = 0;
}

bool is_empty(struct deque *d)
{
    if (d->front == d->rear) {
        return true;
    }
    return false;
}

bool is_full(struct deque *d)
{
    if (d->front == (d->rear + 1) % MAX_DEQUEU_SIZE) {
        return true;
    }
    return false;
}

void push_front(struct deque *d, int val)
{
    if (!is_full(d)) {
        d->front = (d->front - 1 + MAX_DEQUEU_SIZE) % MAX_DEQUEU_SIZE;
        d->elements[d->front] = val;
    }
}

void push_back(struct deque *d, int val)
{
    if (!is_full(d)) {
        d->elements[d->rear] = val;
        d->rear = (d->rear + 1) % MAX_DEQUEU_SIZE;
    }
}

int pop_front(struct deque *d)
{
    if (!is_empty(d)) {
        int val = d->elements[d->front];
        d->front = (d->front + 1) % MAX_DEQUEU_SIZE;
        return val;
    }
    return INT_MAX;
}

int pop_back(struct deque *d)
{
    if (!is_empty(d)) {
        int val = d->elements[d->rear];
        d->rear = (d->rear - 1) % MAX_DEQUEU_SIZE;
        return val;
    }
    return INT_MAX;
}

