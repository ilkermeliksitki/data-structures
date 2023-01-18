#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100000

struct duple {
    int a;
    int b;
};

struct min_heap {
    int size;
    int H[MAX_HEAP_SIZE];
    int duple_size;
    struct duple *output;
};

/* function prototypes */
void swap(int *, int *);
int left_child(int);
int right_child(int);
int parent(int);
struct min_heap *init_heap(int);
void build_heap(struct min_heap *);
void sift_down(struct min_heap *, int);
void add_duple(struct min_heap *, int, int);

int main(void)
{
    /* get the length of the array */
    int n;
    scanf("%d", &n);
    
    /* initialize the heap */
    struct min_heap *h = init_heap(n);

    /* get array and put them into H in min_heap structure */
    for (int i = 0; i < n; ++i) {
        scanf("%d", &h->H[i]);
    }

    /* builds min-heap array, which is stored in h->H */
    build_heap(h);

    /* print output, which is stored in the output in min_heap */
    printf("%d\n", h->duple_size);
    for (int i = 0; i < h->duple_size; ++i) {
        printf("%d %d\n", h->output[i].a, h->output[i].b);
    }

    /* free up the memory locations */
    free(h->output);
    free(h);
    return 0;
}

void build_heap(struct min_heap *h)
{
    /**
     * floor(size/2) gives the index of the smallest tree other than leafs.
     * by traversing all possible tree pieces and with the help of 
     * sift_down function, the whole min-heap tree become complete.
     */
    for (int i = h->size / 2; i >= 0 ; --i) {
        sift_down(h, i);
    }
}

void sift_down(struct min_heap *h, int i)
{
    int min_index = i;
    int l = left_child(i);

    /* l is in the limits of heap and child is smaller than its parent */
    if (l < h->size && h->H[l] < h->H[min_index]) {
        min_index = l;
    }

    /* r is in the limits of heap and child is smaller than its parent */
    int r = right_child(i);
    if (r < h->size && h->H[r] < h->H[min_index]) {
        min_index = r;
    }

    /**
     * if i != min_index, that means we have to do swap operation to make 
     * the tree complete and have to do sift_down operations. add_duple 
     * function is for storing the swapped indexes (for output)
     */
    if (i != min_index) {
        add_duple(h, i, min_index);
        swap(&h->H[i], &h->H[min_index]);
        sift_down(h, min_index);
    }
}

void add_duple(struct min_heap *h, int a, int b)
{
    /**
     * dynamically allocates memory for each duple (swapped indexes)
     * and allocated memory grows if needed by using realloc() function
     * and then, the duple is added ath the and of the allocated memory.
     */
    struct duple d;
    d.a = a;
    d.b = b;
    if (h->duple_size == 0) {
        h->duple_size++;
        h->output = malloc(sizeof(struct duple));
        h->output[h->duple_size - 1] = d;
    } else {
        h->duple_size++;
        h->output = realloc(h->output, sizeof(struct duple) * h->duple_size);
        h->output[h->duple_size - 1] = d;
    }
}

struct min_heap *init_heap(int n)
{
    /* initialize min-heap */
    struct min_heap *h = malloc(sizeof(struct min_heap));
    h->size = n;
    h->duple_size = 0;
    return h;
}

int parent(int i)
{
    return (i - 1) / 2;
}

int left_child(int i)
{
    return 2*i + 1;
}

int right_child(int i)
{
    return 2*i +2;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

