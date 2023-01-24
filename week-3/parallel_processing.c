#include <stdio.h>
#include <stdlib.h>

struct assigned_job {
    int worker;
    long int started_at;
};

/* function prototype */
struct assigned_job *assign_jobs(int, long int *, int);

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

struct assigned_job *assign_jobs(int n_workers, long int *jobs, int n_jobs)
{
    struct assigned_job *result = malloc(sizeof(struct assigned_job) * n_jobs);

    /* allocate and init with 0 */
    long int *next_free_time = calloc(n_workers, sizeof(long int));
    for (int i = 0; i < n_jobs; ++i) {
        int next_worker = 0;
        for (int j = 0; j < n_workers; ++j) {
            if (next_free_time[j] < next_free_time[next_worker]) {
                next_worker = j;
            }
        }
        result[i].worker = next_worker;
        result[i].started_at = next_free_time[next_worker];
        next_free_time[next_worker] += jobs[i];
    }

    free(next_free_time);
    return result;
}
