#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    int num_children;
    struct node** children;
};

struct node* create_node(int key, int num_children)
{
    struct node* n = (struct node*)malloc(sizeof(struct node*));
    n->key = key;
    n->num_children = num_children;
    n->children = (struct node**)malloc(num_children * sizeof(struct node*));
    return n;
}

void add_child(int parent_key, int child_key, struct node* nodes[], int n)
{
    for (int i = 0; i < n; i++){
        if (nodes[i]->key == parent_key) {
            for (int j = 0; j < nodes[i]->num_children; j++){
                if (nodes[i]->children[j] == NULL){
                    nodes[i]->children[j] = nodes[child_key];
                    return;
                }
            }
        }
    }
}

int tree_height(struct node* root)
{
    if (root == NULL)
        return 0;

    int curr_height = 0;
    for (int i = 0; i < root->num_children; i++){
        int child_height = tree_height(root->children[i]);
        if (child_height > curr_height){
            curr_height = child_height;
        }
    }
    return 1 + curr_height;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    int keys[n];
    for (int i = 0; i < n; i++){
        scanf("%d", &keys[i]);
    }

    int num_children_arr[n];
    for (int i = 0; i < n; i++){
        num_children_arr[i] = 0;
    }

    int root_idx;
    for (int i = 0; i < n; i++){
        if (keys[i] != -1) {
            num_children_arr[keys[i]]++;
        } else {
            root_idx = i;
        }
    }
    struct node* nodes[n];
    for (int i = 0; i < n; i++){
        nodes[i] = create_node(i, num_children_arr[i]);
    }
    for (int i = 0; i < n; i++){
        add_child(keys[i], i, nodes, n);
    }

    int h = tree_height(nodes[root_idx]);
    printf("%d\n", h);

    /* deallocation part */
    for (int i = 0; i < n; i++){
        free(nodes[i]);
    }
    
    return 0; 
}
