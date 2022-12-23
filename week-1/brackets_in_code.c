#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX_STACK_SIZE 100000

typedef struct{
    char c;
    int idx;
} parenthesis;

parenthesis stack[MAX_STACK_SIZE];
int top_idx = -1;

void push(int i, char val);
parenthesis pop();
bool is_empty();
parenthesis peek();
bool is_pair(char a, char b);
int is_balanced(char *str);

int main(void)
{
    char str[1000000]; 
    scanf("%s", str);

    int r = is_balanced(str);
    if (r == 0){
        printf("%s\n", "Success");
    } else {
        printf("%d\n", r);
    }
    return 0;
}

int is_balanced(char *str)
{
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            push(i, str[i]);
        } else if (str[i] == ')' || str[i] == ']' || str[i] == '}') {
            if (is_pair(peek().c, str[i])) {
                pop();
            } else {
                return i + 1;
            }
        }
    }
    if (is_empty()) {
        return 0;
    }
    else {
        /* if the stack is not empy, just return the index(1-based) of top element */
        return peek().idx + 1;
    }
}

bool is_pair(char a, char b)
{
    /* note that this is a one directional pair function */ 
    if (a == '(' && b == ')')
        return true;
    else if (a == '[' && b == ']')
        return true;
    else if (a == '{' && b == '}')
        return true;
    else
        return false;
}

void push(int i, char val)
{
    /* stack is full */
    if (top_idx == MAX_STACK_SIZE - 1)
        return;
    parenthesis p;
    p.c = val;
    p.idx = i;
    stack[++top_idx] = p;
}

parenthesis peek()
{
    if (top_idx == -1) {
        parenthesis p;
        p.idx = -1;
        return p;
    }
    return stack[top_idx];
}

parenthesis pop()
{
    /* stack is empty */
    if (top_idx == -1){
        parenthesis p;
        p.idx = -1;
        return p;
    }
    return stack[top_idx--];
}

bool is_empty()
{
    if (top_idx == -1)
        return true;
    else
        return false;
}
