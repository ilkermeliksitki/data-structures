#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *left;
    struct node *right;
};

struct node* create_node(int key, struct node* l, struct node* r)
{
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->key = key;
    n->left = l;
    n->right = r;
    return n;
}

void fill_node(struct node* nodes[], int n, int val, int pos)
{
    for (int i = 0; i < n; i++){
        if (nodes[i]->key == val) {
            if (nodes[i]->left == NULL) {
                nodes[i]->left = nodes[pos];
            } else if (nodes[i]->right == NULL){
                nodes[i]->right = nodes[pos];
            } else {
                printf("%s\n", "wrong format");
                return;
            }
        }
    }
}


int tree_height(struct node* nodes[], int n)
{
    return 99;
}

int main(void)
{
    int n;
    scanf("%d", &n);

    struct node* nodes[n];
    for (int i = 0; i < n; i++){
        nodes[i] = create_node(i, NULL, NULL);
    }

    int val;
    for (int i = 0; i < n; i++){
        scanf("%d", &val);
        fill_node(nodes, n, val, i);
    }
    
    //int h = tree_height(nodes, n);
    //printf("%d\n", h);

    /* deallocate the allocated part of the heap */
    for (int i = 0; i < n; i++){
        free(nodes[i]);
    }

    return 0; 
}
