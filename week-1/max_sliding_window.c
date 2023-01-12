#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_DEQUEU_SIZE 100000

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
int get_front(struct deque *);
int get_back(struct deque *);

int main(void)
{
    int n;
    scanf("%d", &n);
    int nums[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &nums[i]);
    }
    int m;
    scanf("%d", &m);

    /**
     * the following deque's buffer (elements) is designed as a circular fashion.
     * the rear and front indexes wrapped around when they exceed the limit of
     * the buffer.
     */
    struct deque *d = malloc(sizeof(struct deque));
    init_deque(d);

    for (int i = 0; i < n; ++i) {
        /**
         * check whether the front element of the deque is in the current window 
         * i - m gives the index of the element that is no longer in the window
         */
        if (!is_empty(d) && get_front(d) == i - m) {
            pop_front(d);
        }
        /**
         * if the back element of the deque is less then the current element, it is
         * not "relevant" anymore, so it is popped.
         */
        while (!is_empty(d) && nums[get_back(d)] < nums[i]) {
            pop_back(d);
        }
        /**
         * add the current element to the back of the deque.
         */
        push_back(d, i);
        /**
         * when the first window is completely added, start writing maximum element, 
         * which is found at the front of the deque, to stdout.
         */
        if (i >= m - 1) {
            printf("%d ", nums[get_front(d)]);
        }
    }
    printf("%c", '\n');

    free(d);
    return 0;
}

int get_front(struct deque *d)
{
    return d->elements[d->front];
}

int get_back(struct deque *d)
{
    return d->elements[d->rear];
}

void init_deque(struct deque *d)
{
    d->front = -1;
    d->rear = -1;
}

bool is_empty(struct deque *d)
{
    if (d->front == -1 && d->rear == -1) {
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
    if (is_empty(d)) {
        d->front = 0;
        d->rear = 0;
        d->elements[0] = val;
    } else {
        if (!is_full(d)) {
            /**
             * when rear index becomes bigger than the size of the deque, 
             * after the push front operation, it wraps around, to the 
             * end. Of course, if it is not full.
             */
            d->front = (d->front - 1 + MAX_DEQUEU_SIZE) % MAX_DEQUEU_SIZE;
            d->elements[d->front] = val;
        }
    }
}

void push_back(struct deque *d, int val)
{
    if (is_empty(d)) {
       d->front = 0;
       d->rear = 0;
       d->elements[0] = val;
    } else {
        if (!is_full(d)) {
            /**
             * when rear index becomes bigger than the size of the deque, 
             * after the push back operation, it wraps around, to the 
             * beginning. Of course, if it is not full.
             */
            d->rear = (d->rear + 1) % MAX_DEQUEU_SIZE;
            d->elements[d->rear] = val;
        }
    }
}

int pop_front(struct deque *d)
{
    if (d->front == d->rear) {
        int val = d->elements[d->front];
        /* reset indexes if deque becomes empty */
        d->front = -1;
        d->rear = -1;
        return val;
    }
    if (!is_empty(d)) {
        int val = d->elements[d->front];
        /**
         * same logic with the push_back operation, be careful not push_front!
         */
        d->front = (d->front + 1) % MAX_DEQUEU_SIZE;
        return val;
    }
    return INT_MAX;
}

int pop_back(struct deque *d)
{
    if (d->front == d->rear) {
        int val = d->elements[d->rear];
        /* reset indexes if deque becomes empty */
        d->front = -1;
        d->rear = -1;
        return val;
    }
    if (!is_empty(d)) {
        int val = d->elements[d->rear];
        /**
         * same logic with the push_front operation, be careful not push_back!
         */
        d->rear = (d->rear - 1) % MAX_DEQUEU_SIZE;
        return val;
    }
    return INT_MAX;
}
