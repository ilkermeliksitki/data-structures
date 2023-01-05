#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_BUFFER_SIZE 100000

typedef struct {
    int arrived_at;
    int time_to_process;
} Request;

typedef struct {
    bool was_dropped;
    int readed_at;
} Response;

/* the buffer is implemented by considering queue data structure
 * (fixed loop-based array implementation)
 */
typedef struct {
    int read;                          // the read index of buffer structure
    int write;                         // the next available position of the new element.
    int size;                          // size of the buffer.
    int finish_time[MAX_BUFFER_SIZE];  // the time that the request finished being processed.
} Buffer;

void init_buffer(Buffer* buffer, int size) {
    buffer->size = size;
    buffer->read = 0;
    buffer->write = 0;
}

Response process(Buffer* buffer, Request* request) {
    Response response;
    /* 
     * this while loop removes the processed and finished requests from the buffer if it is not empty
     * by incrementing the read index by one.
     */
    while (buffer->read != buffer->write && buffer->finish_time[buffer->read] <= request->arrived_at) {
        /* % MAX_BUFFER_SIZE sends the read index to the beginning if it exceed the the size of the buffer */
        buffer->read = (buffer->read + 1) % MAX_BUFFER_SIZE;
    }
    int packets_in_buffer = (buffer->write - buffer->read + MAX_BUFFER_SIZE) % MAX_BUFFER_SIZE;
    if (packets_in_buffer == buffer->size) {
        response.was_dropped = true;
        response.readed_at = -1;
    } else {
        /* 
         * if there is no packet, process the request immediately at arrived time
         * else, the request should wait until the previous request is finished
         * so in this case, readed_at time is equal to previous request's finish_time. 
         */
        response.was_dropped = false;
        if (packets_in_buffer == 0) {
            response.readed_at = request->arrived_at;
        } else {
            response.readed_at = buffer->finish_time[(buffer->write - 1 + MAX_BUFFER_SIZE) % MAX_BUFFER_SIZE];
        }
        /*
         * finish_time of the current request is the sum of the time that has been read
         * plus the process time.
         */
        buffer->finish_time[buffer->write] = response.readed_at + request->time_to_process;
        buffer->write = (buffer->write + 1) % MAX_BUFFER_SIZE;
    }
    return response;
}

void process_requests(Response* responses, Buffer* buffer, Request* requests, int n) {
    for (int i = 0; i < n; i++) {
        responses[i] = process(buffer, &requests[i]);
    }
}

int main(int argc, char** argv) {
    int S, n;
    scanf("%d %d", &S, &n);

    Request requests[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &requests[i].arrived_at, &requests[i].time_to_process);
    }

    Buffer buffer;
    init_buffer(&buffer, S);
    Response responses[n];
    process_requests(responses, &buffer, requests, n);
    for (int i = 0; i < n; i++) {
        printf("%d\n", (responses[i].was_dropped ? -1 : responses[i].readed_at));
    }
    
    return 0;
}
