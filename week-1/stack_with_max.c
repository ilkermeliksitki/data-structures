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
    /**
     * initialize the stack and top index, 
     * this is the main stack that store the elements
     */
    Stack *stack = malloc(sizeof(Stack));
    stack->top = -1;

    /**
     * this stack is for keeping track of maximum value
     * of the stack, by doing this we can find the maximum
     * value of the previous stack in constant time.
     */
    Stack *max_val_stack = malloc(sizeof(Stack));
    max_val_stack->top = -1;

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
            /**
             * push case
             * if the current value v is bigger than or equal to the top max_val_stack 
             * element, v value is also pushed to max_val_stack.
             *
             */
            push(stack, v);
            if (is_empty(max_val_stack)) {
                push(max_val_stack, v);
            } else {
                if (v >= max_val_stack->elements[max_val_stack->top]) {
                    push(max_val_stack, v);
                }
            }
        } else if (num == 1){
            if (strcmp(command, "pop") == 0) {
                /**
                 * if the top values of both stack are equal to each other, pop the 
                 * elements of both stack, if not, pop only the main stack.
                 */
                if (stack->elements[stack->top] == max_val_stack->elements[max_val_stack->top]){
                    pop(max_val_stack);
                }
                pop(stack);
            } else if (strcmp(command, "max") == 0){
                int max_element = max_val_stack->elements[max_val_stack->top];
                printf("%d\n", max_element);
            } 
        }
    }
    
    free(max_val_stack);
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

bool is_empty(Stack *stack)
{
    if (stack->top == -1) {
        return true;
    }
    return false;
}
