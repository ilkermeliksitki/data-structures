#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


struct Node {
    int key;
    int left;
    int right;
};

// function prototypes
bool is_binary_search_tree(struct Node **tree, int index, int min, int max);

int main(void)
{
    int nodes;
    scanf("%d", &nodes);
    if (nodes == 0) {
        printf("%s\n", "CORRECT");
        return 0;
    }

    struct Node **tree = malloc(sizeof(struct Node *) * nodes);
    // fill tree
    int key, left, right;
    for (int i = 0; i < nodes; ++i) {
        scanf("%d %d %d", &key, &left, &right);
        struct Node *node = malloc(sizeof(struct Node));
        node->key = key;
        node->left = left;
        node->right = right;
        tree[i] = node;
    }

    if (is_binary_search_tree(tree, 0, 0, INT_MAX)) {
        printf("%s\n", "CORRECT");
    } else {
        printf("%s\n", "INCORRECT");
    }

    // free memory
    for (int i = 0; i < nodes; ++i) {
        free(tree[i]);
    }
    free(tree);

    return 0;
}

bool is_binary_search_tree(struct Node **tree, int index, int min, int max)
{
    // leaf node case, if index = -1, then it is a leaf node.
    if (index == -1)
        return true;

    // key should be in the range
    if (tree[index]->key < min || tree[index]->key > max)
        return false;

    // recursively check the range of keys of the nodes
    return is_binary_search_tree(tree, tree[index]->left, min, tree[index]->key) && 
           is_binary_search_tree(tree, tree[index]->right, tree[index]->key + 1, max );
}
