#include "queue.h"
#include <stdlib.h>

Queue* queue_construct(){
    Queue *queue = (Queue*) calloc(1, sizeof(Queue));
    queue->vector = vector_construct();
    return queue;
}

void queue_enqueue(Queue *queue, void *item){
    vector_push_back(queue->vector, item);
}
void* queue_dequeue(Queue *queue){
    if (queue_size(queue) > 0){
       return vector_pop_front(queue->vector);
    }else{
        return NULL;
    }
}

int queue_size(Queue *queue){
    
    return vector_size(queue->vector);
}

void queue_destruct(Queue *queue){
    while (queue_size(queue) > 0) {
        free(queue_dequeue(queue));
    }
    vector_destroy(queue->vector);
    free(queue);
}