#include <stdio.h>
#include <stdlib.h>

struct assigned_job {
    int worker;
    long int started_at;
};

struct node {
    int index;
    long int value;
};

struct min_heap {
    int size;
    struct node *H;
};

/* function prototype */
struct assigned_job *assign_jobs(int, long int *, int);
void build_heap(struct min_heap *);
void sift_down(struct min_heap *, int);
void sift_up(struct min_heap *, int);
struct node extract_min(struct min_heap *);

int main(void)
{
    int n_workers, n_jobs;
    scanf("%d %d", &n_workers, &n_jobs);

    long int *jobs = malloc(sizeof(long int) * n_jobs);
    for (int i = 0; i < n_jobs; ++i) {
        scanf("%d", &jobs[i]);
    }

    struct assigned_job *assigned_jobs = assign_jobs(n_workers, jobs, n_jobs);
    for (int i = 0; i < n_jobs; ++i) {
        printf("%d %lld\n", assigned_jobs[i].worker, assigned_jobs[i].started_at);
    }

    free(jobs);
    free(assigned_jobs);
    return 0;
}

struct min_heap *init_heap(int heap_size)
{
    struct min_heap *h = malloc(sizeof(struct min_heap));
    h->H = malloc(heap_size * sizeof(struct node));
    h->size = 0;
    return h;
}

void build_heap(struct min_heap *h)
{
    for (int i = h->size / 2; i >= 0; --i) {
        sift_down(h, i);
    }
}

struct assigned_job *assign_jobs(int n_workers, long int *jobs, int n_jobs)
{
    struct assigned_job *result = malloc(sizeof(struct assigned_job) * n_jobs);
    
    /**
     * Initialize min-heap, and fill H attribute of it. The value of the nodes are
     * all zero at first because the heap represents the next free time as value.
     * Next lines set the size of the heap and `build` the heap.
     */
    struct min_heap *h = init_heap(n_workers);
    for (int i = 0; i < n_workers; ++i) {
        struct node n = {i, 0};
        h->H[i] = n;
    }
    h->size = n_workers;
    build_heap(h);

    /**
     * By using min-heap data structure, we can get the node with mininum next
     * free time with an O(logk) complexity. So this reduces the complexity of 
     * assign_jobs function to O(n logk), where n is the number of job, and k 
     * is the number of threads(worker). (The complexity of naive algorithm is
     * O(n^2)).
     * 
     * The next free time of the node is updated with job time, then the node is
     * inserted back to the heap and sorted by using sift_up function, which
     * makes the heap such a way that the root of the heap is always earliest
     * next free time.
     */
    for (int i = 0; i < n_jobs; ++i) {
        struct node new_worker = extract_min(h);
        result[i].worker = new_worker.index;
        result[i].started_at = new_worker.value;
        new_worker.value += jobs[i];
        h->H[h->size] = new_worker;
        h->size++;
        sift_up(h, h->size - 1);
    }

    free(h->H);
    free(h);
    return result;
}

struct node extract_min(struct min_heap *h)
{
    /**
     * save the root of the heap for returning puposes, get the `last` element of the
     * heap, and put it to the location of the root, reduce the size by 1 and apply
     * sift_down function for sorting the heap again.
     */
    struct node min = h->H[0]; 
    h->H[0] = h->H[h->size - 1];
    h->size--;
    sift_down(h, 0);
    return min;
}

void swap(struct node *a, struct node *b)
{
    struct node temp = *a;
    *a = *b;
    *b = temp;
}

int compare_nodes(struct node a, struct node b)
{
    /**
     * this is an helper function and compares two nodes and return 1, if the first one
     * is smaller than the second one. otherwise it returns 0.
     *
     * if the values of the nodes are the same, then it compares the indexes and return
     * 1 if the first one's index is smaller than the second one, otherwise it return 0
     *
     * this function is used in sift_down and sift_up functions for the purpose of making
     * readable if and while statement conditions.
     */
    if (a.value != b.value) {
        return a.value < b.value;
    }
    return a.index < b.index;
}

void sift_down(struct min_heap *h, int i)
{
    /**
     * sift_down function is used to sort recursively the heap and put the nodes
     * having larger values down by doing swap operations. Additionally, sift_down
     * function uses compare_nodes function as a helper function for sorting nodes
     * considering also the indexes of the nodes. Look at compare_nodes function.
     */
    int min_index = i;

    int l = 2 * i + 1;
    if (l < h->size && compare_nodes(h->H[l], h->H[min_index])){
        min_index = l;
    }

    int r = 2 * i + 2;
    if (r < h->size && compare_nodes(h->H[r], h->H[min_index])) {
        min_index = r;
    }

    if (i != min_index) {
        swap(&h->H[i], &h->H[min_index]);
        sift_down(h, min_index);
    }
}

void sift_up(struct min_heap *h, int i)
{
    /**
     * sift_up function is used to sort nodes in the heap toward the root of the heap.
     * It also use compare_nodes function as a helper function. 
     */
    int parent = (i - 1) / 2;
    while (i > 0 && compare_nodes(h->H[i], h->H[parent]))
    {
        swap(&h->H[parent], &h->H[i]);
        i = parent;
        parent = (i - 1) / 2;
    }
}
