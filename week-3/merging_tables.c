#include <stdio.h>
#include <stdlib.h>

struct database {
    int max_row_count;
    int n_tables;
    int *row_counts;
    int *ranks;
    int *parents;
};

/* function prototypes */
int get_parent(struct database *, int);
int merge(struct database *db, int, int);
struct database *create_database(int *, int);
void destroy_database(struct database *);

int main(void)
{
    int n_tables, n_queries;
    scanf("%d %d", &n_tables, &n_queries);
    int *counts = malloc(sizeof(int) * n_tables);
    for (int i = 0; i < n_tables; ++i) {
        scanf("%d", &counts[i]);
    }
    struct database *db = create_database(counts, n_tables);
    for (int i = 0; i < n_queries; ++i) {
        int dst, src;
        scanf("%d %d", &dst, &src);
        /* turn it into 0-based array */
        merge(db, dst - 1, src - 1);
        printf("%d\n", db->max_row_count);
    }

    destroy_database(db);
    return 0;
}

int get_parent(struct database *db, int table)
{
    /* find parent and compress path */
    if (table != db->parents[table]) {
        db->parents[table] = get_parent(db, db->parents[table]);
    }
    return db->parents[table];
}

int merge(struct database *db, int src, int dst)
{
    int src_parent = get_parent(db, src);
    int dst_parent = get_parent(db, dst);
    if (src_parent == dst_parent) {
        return 0;
    }
    /**
     * merge two components
     * use union by rank heuristic
     * update max_row_count with the new maximum table size
     */
    if (db->ranks[src_parent] > db->ranks[dst_parent]) {
        /* dst_parent become the child of src_parent */
        db->parents[dst_parent] = src_parent;
        db->row_counts[src_parent] += db->row_counts[dst_parent];
        db->row_counts[dst_parent] = 0;
        if (db->row_counts[src_parent] > db->max_row_count) {
            db->max_row_count = db->row_counts[src_parent];
        }
    } else {
        /* src_parent become the child of dst_parent */
        db->parents[src_parent] = dst_parent;
        db->row_counts[dst_parent] += db->row_counts[src_parent];
        db->row_counts[src_parent] = 0;
        if (db->row_counts[dst_parent] > db->max_row_count) {
            db->max_row_count = db->row_counts[dst_parent];
        }
        if (db->ranks[src_parent] == db->ranks[dst_parent]) {
            db->ranks[src_parent]++;
        }
    }
    return 1;
}

struct database *create_database(int *row_counts, int n_tables)
{
    struct database *db = malloc(sizeof(struct database));
    db->row_counts = row_counts;
    db->n_tables = n_tables;
    db->max_row_count = 0;

    /* find the maximum number of row */
    for (int i = 0; i < n_tables; ++i) {
        if (row_counts[i] > db->max_row_count) {
            db->max_row_count = row_counts[i];
        }
    }

    /* set the rank of all tables to 1 */
    db->ranks = malloc(sizeof(int) * n_tables);
    for (int i = 0; i < n_tables; ++i) {
        db->ranks[i] = 1;
    }

    /* at first, the parent of tables are themselves */
    db->parents = malloc(sizeof(int) * n_tables);
    for (int i = 0; i < n_tables; ++i) {
        db->parents[i] = i;
    }
    return db;
}

void destroy_database(struct database *db)
{
    free(db->row_counts);
    free(db->ranks);
    free(db->parents);
    free(db);
}
