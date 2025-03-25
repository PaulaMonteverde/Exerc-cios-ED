#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct Queue Queue;

Queue *queue_construct();
void queue_destroy(Queue *q);
int queue_size(Queue *q);
void queue_push(Queue *q, void *data);
void* queue_pop(Queue *q);


#endif