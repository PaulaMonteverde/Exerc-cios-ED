#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "node.h" 

List *list_construct(){
    
    List *l = calloc(1, sizeof(List));
    l->size = 0;
    l->head = NULL;
    l->last = NULL;

    return l;
}
int list_size(List *l){
    return l->size;
}
void list_push_front(List *l, data_type data){
    if (l->head == NULL){
        l->head = node_construct(data, NULL, NULL);
        l->size++;
    }else {
        Node *aux = NULL;
        aux = l->head; //antiga cabeça;
        l->head = node_construct(data, NULL, l->head);// nova cabeça;
        l->last = aux; //aponta para a antiga cabeça;
        l->size++;
    }
    

}
void list_print(List *l, void (*print_fn)(data_type)){
    if (l->head == NULL || l == NULL){
        printf("[]\n");
        return;
    }

    Node *atual = l->head;
    printf("[");

    while(atual != NULL){
        if (atual != NULL){
            print_fn(atual->value);
             if(atual->next != NULL){
                 printf(", ");
             }
        }
        atual = atual->next;
    }
    printf("]\n");
}
void list_destroy(List *l){
    Node* n = l->head;
    while (n != NULL){
        Node *next = n->next;
        node_destroy(n);
        n = next;
    }
    free(l);
}
