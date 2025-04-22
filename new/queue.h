#ifndef QUEUE_H
#define QUEUE_H

/* monotonic queue for float values */
/* using circular queue */
typedef struct 
{
    float* data; 
    int* indices; 
    int front; /* front position of the queue  */
    int rear;  /* next position to be enqueued */
    int window_size;
}monotonic_queue;


void init_queue( monotonic_queue* q, int window_size );
int isempty( monotonic_queue* q );
float get_front( monotonic_queue* q );
void free_queue( monotonic_queue* q );
void enqueue( monotonic_queue* q, float value, int index, int (*compare)(float, float) );
int max_compare( float a, float b );
int min_compare( float a, float b );
void dequeue( monotonic_queue* q, int window_start );

#endif 


