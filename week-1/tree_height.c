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

void add_child(int parent_key, int child_key, struct node* nodes[], int null_indexes[])
{
    struct node* parent_node;
    parent_node = nodes[parent_key];
    int null_idx = null_indexes[parent_key];
    parent_node->children[null_idx] = nodes[child_key];
    null_indexes[parent_key]++;
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

void free_nodes(struct node* n)
{
    for (int i = 0; i < n->num_children; i++){
        free_nodes(n->children[i]);
    }
    /* deallocate children array */
    free(n->children);
    /* deallocate the node itself */
    free(n);
}

int main(void)
{
    int n;
    scanf("%d", &n);
    int keys[n];
    for (int i = 0; i < n; i++){
        scanf("%d", &keys[i]);
    }

    /*
     * null_index_of_parents keeps track of available child location for adding.
     * num_children_arr keeps track of the number of children of every node. Every
     * node can have variable number of children.
     */
    int null_index_of_parents[n];
    int num_children_arr[n];
    for (int i = 0; i < n; i++){
        num_children_arr[i] = 0;
        null_index_of_parents[i] = 0; 
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
        /* root node doesn't have a parent, so it is skipped. */
        if (keys[i] == -1)
            continue;
        add_child(keys[i], i, nodes, null_index_of_parents);
    }

    int h = tree_height(nodes[root_idx]);
    printf("%d\n", h);

    /*
     * deallocation of dynamically allocated structure nodes, increase computation time
     * a little bit.
     */
    free_nodes(nodes[root_idx]);
    return 0; 
}
