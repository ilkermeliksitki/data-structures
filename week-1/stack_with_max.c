#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACK_SIZE 400000

typedef struct {
    int top;
    int elements[STACK_SIZE];
} Stack;

void push(Stack *, int);
int pop(Stack *);
bool is_empty(Stack *);
int find_max(Stack *);

int main(void)
{
    /* initialize the stack and top index */
    Stack *stack = malloc(sizeof(Stack));
    stack->top = -1;

    int q;
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &q);

    int v;
    char command[6];
    for (int i = 0; i < q; ++i) {
        fgets(buffer, sizeof(buffer), stdin);
        int num = sscanf(buffer, "%s %d", command, &v);
        if (num == 2){
            /* push case */
            push(stack, v);
        } else if (num == 1){
            if (strcmp(command, "pop") == 0) {
                /* pop case */
                pop(stack);
            } else if (strcmp(command, "max") == 0){
                int max = find_max(stack);
                printf("%d\n", max);
            } 
        }
    }
    

    free(stack);
    return 0;
}

void push(Stack *stack, int element)
{
    if (stack->top >= STACK_SIZE - 1) {
        fprintf(stderr, "stack overflow\n");
        exit(1);
    }
    /* add `element` to the top of the stack */
    stack->elements[++stack->top] = element;
}

int pop(Stack *stack)
{
    if (stack->top < -1) {
        fprintf(stderr, "stack underflow\n");
        exit(2);
    }
    return stack->elements[stack->top--];
}

int find_max(Stack *stack)
{
    int max_element = INT_MIN;
    int top_idx = stack->top;
    for (int i = 0; i <= top_idx; ++i) {
        if (stack->elements[i] > max_element) {
            max_element = stack->elements[i];
        }
    }
    return max_element;
}

bool is_empty(Stack *stack)
{
    if (stack->top == -1) {
        return true;
    }
    return false;
}
