#include "global.h"

void init_queue(monotonic_queue* q, int window_size) 
{
    q->window_size = window_size;
    q->data = (float*) malloc(window_size * sizeof(float));
    q->indices = (int*) malloc(window_size * sizeof(int));
    q->front = 0; /* front position of the queue */
    q->rear = 0;  /* next position to be enqueued */
}

void free_queue(monotonic_queue* q) 
{
    free(q->data);
    free(q->indices);
}

int isempty(monotonic_queue* q) 
{
    return q->rear == q->front;
}

/* get max or min in the queue */
float get_front(monotonic_queue* q)  
{
    return q->data[q->front];
}

/* enqueue an element to the queue */
void enqueue(monotonic_queue* q, float value, int index, int (*compare)(float, float)) 
{
    int tail;
    tail = (q->rear - 1 + q->window_size) % q->window_size; /* point to the last element */
    while (!isempty(q) && compare(q->data[tail], value))
    {
        q->rear = tail;
        tail = (q->rear - 1 + q->window_size) % q->window_size;
    }

    /* enqueue the new element */
    q->data[q->rear] = value;
    q->indices[q->rear] = index;

    q->rear = (q->rear + 1) % q->window_size;
}

int max_compare(float a, float b) 
{
    return a <= b;
}

int min_compare(float a, float b) 
{
    return a >= b;
}

/* dequeue the front element (when the window slides out of range) */
void dequeue(monotonic_queue* q, int window_start) 
{
    while (!isempty(q) && q->indices[q->front] < window_start)
        q->front = (q->front + 1) % q->window_size;
}

/*
example:
int main(void)
{
    float a[] = {2.3, 6.7, 4.5, 8.9, 1.2, 3.4, 5.6};
    int size = sizeof(a) / sizeof(a[0]);
    monotonic_queue q;
    int i;
    init_queue(&q, 3);
    for (i = 0; i < size; i++)
    {
        enqueue_max(&q, a[i], i);
        dequeue(&q, i - q.window_size + 1);
        if (i >= q.window_size - 1)
            printf("%f \n", get_front(&q));
    }
    return 0;
}
*/