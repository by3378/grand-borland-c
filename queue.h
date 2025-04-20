#ifndef QUEUE_H
#define QUEUE_H

/* monotonic queue for float values */
/* using circular queue */
typedef struct 
{
    float* data; 
    int* indices; 
    int front; /* front position of the queue */
    int rear; /* next position to be enqueued */
    int window_size 
} monotonic_queue;


void init_queue( monotonic_queue* q, int window_size) ;
int isEmpty( monotonic_queue* q) ;
float get_front( monotonic_queue* q) ;
void free_queue( monotonic_queue* q) ;
/* enqueue an element to max queue */
void enqueue_max( monotonic_queue* q, float value, int index) ;
/* enqueue an element to min queue */
void enqueue_min( monotonic_queue* q, float value, int index) ;
/* dequeue the front element (when the window slides out of range) */
void dequeue( monotonic_queue* q, int window_start) ;

#endif 


