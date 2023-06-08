#include <stdio.h>
#include <stdlib.h>

struct TreeOrders {
    int n;            // number of vertices
    int *key;         // keys of the vertices
    int *left;        // index of the left children
    int *right;       // index of the right children
    int *result;      // result array
    int result_idx;   // index for updating result array
};

/* function prototypes */
void read(struct TreeOrders *);
void traverse(struct TreeOrders *, int, int);
void print_results(struct TreeOrders *);

int main(void)
{
    struct TreeOrders *tree = malloc(sizeof(struct TreeOrders));
    read(tree);
    tree->result = malloc(sizeof(int) * 3 * tree->n);

    tree->result_idx = 0;    // reset result_idx before traversal
    traverse(tree, 0, 1);    // in-order traverse

    tree->result_idx = tree->n;   // reset result_idx before traversal
    traverse(tree, 0, 0);    // pre-order traverse

    tree->result_idx = 2 * tree->n;   // reset result_idx before traversal
    traverse(tree, 0, 2);    // post-order traverse

    // print the results
    print_results(tree);

    // free the memory
    free(tree->key);
    free(tree->left);
    free(tree->right);
    free(tree->result);
    free(tree);

    return 0;
}

void traverse(struct TreeOrders *tree, int i, int order)
{
    if (i == -1)
        return;
    // pre-order 
    if (order == 0)
        tree->result[tree->result_idx++] = tree->key[i];
    traverse(tree, tree->left[i], order);
    // in-order
    if (order == 1)
        tree->result[tree->result_idx++] = tree->key[i];
    traverse(tree, tree->right[i], order);
    // post-order
    if (order == 2)
        tree->result[tree->result_idx++] = tree->key[i];
}


void read(struct TreeOrders *tree)
{
    scanf("%d", &tree->n);
    tree->key = malloc(tree->n * sizeof(int));
    tree->left = malloc(tree->n * sizeof(int));
    tree->right = malloc(tree->n * sizeof(int));
    for (int i = 0; i < tree->n; ++i) {
        scanf("%d %d %d", &tree->key[i], &tree->left[i], &tree->right[i]);
    }
}


void print_results(struct TreeOrders *tree)
{
    for (int order = 0; order < 3; ++order) {
        for (int i = 0; i < tree->n; ++i) {
            printf("%d", tree->result[order * tree->n + i]);
            if (i < tree->n - 1)
                printf("%s", " ");
        }
        printf("%s", "\n");
    }
}
