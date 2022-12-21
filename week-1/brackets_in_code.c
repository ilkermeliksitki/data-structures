#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX_STACK_SIZE 100000

char stack[MAX_STACK_SIZE];
int top_idx = -1;

void push(char val);
char pop();
bool is_empty();
char peek();
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
            push(str[i]);
        } else if (str[i] == ')' || str[i] == ']' || str[i] == '}') {
            if (is_pair(peek(), str[i])) {
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
        return top_idx + 1;
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

void push(char val)
{
    /* stack is full */
    if (top_idx == MAX_STACK_SIZE - 1)
        return;
    stack[++top_idx] = val;
}

char peek()
{
    if (top_idx == -1) {
        return -1;
    }
    return stack[top_idx];
}

char pop()
{
    /* stack is empty */
    if (top_idx == -1)
        return -1;
    return stack[top_idx--];
}

bool is_empty()
{
    if (top_idx == -1)
        return true;
    else
        return false;
}
