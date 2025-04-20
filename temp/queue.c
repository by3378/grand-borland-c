#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

/* initialize the queue */
void init_queue( monotonic_queue* q, int window_size) 
{
    q->window_size = window_size;
    q->data = (float*) malloc( window_size * sizeof(float));
    q->indices = (int*) malloc( window_size * sizeof(int));
    q->front = 0;
    q->rear = 0;
}

/* return true if the queue is empty */
int isEmpty( monotonic_queue* q) 
{
    return q->rear == q->front;
}

/* get max or min in the queue */
float get_front( monotonic_queue* q) 
{
    return q->data[q->front];
}

void free_queue( monotonic_queue* q) 
{
    free(q->data);
    free(q->indices);
}


/* enqueue an element to max queue */
void enqueue_max( monotonic_queue* q, float value, int index) 
{
    /* delete all elements smaller than the current value from the rear */
    int tail = (q->rear-1+q->window_size) % q->window_size;/* the last member of the queue */
    while (!isEmpty(q) && q->data[tail] <= value)
    {
        q->rear=tail;
        tail = (q->rear-1+q->window_size) % q->window_size;
    }

    /* enqueue the new element */
    q->data[q->rear] = value;
    q->indices[q->rear] = index;

    q->rear = (q->rear + 1) % q->window_size;
}
/* enqueue an element to min queue */
void enqueue_min( monotonic_queue* q, float value, int index) 
{
    /* delete all elements smaller than the current value from the rear */
    int tail = (q->rear-1+q->window_size) % q->window_size;/* the last member of the queue */
    while (!isEmpty(q) && q->data[tail] >= value)
    {
        q->rear=tail;
        tail = (q->rear-1+q->window_size) % q->window_size;
    }

    /* enqueue the new element */
    q->data[q->rear] = value;
    q->indices[q->rear] = index;
    
    q->rear = (q->rear + 1) % q->window_size;
}


/* dequeue the front element (when the window slides out of range) */
void dequeue( monotonic_queue* q, int window_start) 
{
    while ( !isEmpty(q) && q->indices[q->front] < window_start)
        q->front = (q->front + 1) % q->window_size;

}

/*
example:
int main(void)
{
    float a[]={2.3,6.7,4.5,8.9,1.2,3.4,5.6};
    int size= sizeof(a)/sizeof(a[0]);
    monotonic_queue q;
    init_queue(&q,3);
    for(int i=0;i<size;i++)
    {
        enqueue_max(&q,a[i],i);
        dequeue( &q, i - q.window_size + 1 );
        if( i >=q.window_size-1 )
            printf("%f \n",get_front(&q));
    }
    return 0;
}
*/