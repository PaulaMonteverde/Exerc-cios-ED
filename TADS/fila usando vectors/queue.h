#ifndef QUEUE_H
#define QUEUE_H

#include "vector.h"

typedef struct queue {
    Vector *vector;
} Queue;

Queue* queue_construct();
void queue_destruct(Queue *queue);
int queue_size(Queue *queue);
void queue_enqueue(Queue *queue, void *item);
void* queue_dequeue(Queue *queue);

#endif