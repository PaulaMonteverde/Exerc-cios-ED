#include "queue.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Queue {
    Node *inicio;
    Node *final;
    int size;
} Queue;

Queue *queue_construct(){
    Queue *q = (Queue*)calloc(1, sizeof(Queue));
    q->inicio = NULL;
    q->final = NULL;
    q->size++;
    return q;
}
void queue_destroy(Queue *q){
    Node* atual = q->inicio; 
    while (atual != NULL){
        Node *aux = atual;
        atual = atual->next;
        free(aux->value);
        node_destroy(aux);
    }
    free(q);
}
int queue_size(Queue *q){
    return q->size;
}
void queue_push(Queue *q, void *data){
    Node* novo_no = node_construct(data, q->final, NULL);
    if (q->inicio == NULL){
        q->inicio = novo_no;
        q->final = novo_no;
    }else{
        q->final->next = novo_no;
        q->final = novo_no;
    }
    q->size++;
}
void* queue_pop(Queue *q){
    data_type valor;
    if (q->inicio != NULL){
        Node* aux = q->inicio;
        valor = q->inicio->value;
        if (q->inicio != NULL){
            q->inicio = q->inicio->next;
        }
        node_destroy(aux);
        q->size--;
    }

    return valor;
}

