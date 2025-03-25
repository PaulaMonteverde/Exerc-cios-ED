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
        l->last = l->head;
        l->size++;
    }else {
        Node* novo_no = node_construct(data, NULL, l->head);
        l->head->prev = novo_no;
        l->head = novo_no;
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

void list_print_reverse(List *l, void (*print_fn)(data_type)){
    if (l == NULL || l->last == NULL){
        printf("[]\n");
        return;
    }

    Node *atual = l->last;
    printf("[");

    while(atual != NULL){
            print_fn(atual->value);
             if(atual->prev != NULL){
                printf(", ");
             }
        atual = atual->prev;
    }
    printf("]\n");
}

data_type list_pop_front(List *l){
    if (l->head == NULL){
        printf("ERRO\n");
        return 0;
    }else {
        data_type valor;
        Node* aux;
        aux = l->head;
        valor = l->head->value;
        l->head = l->head->next;
        l->head->prev = NULL;
        node_destroy(aux);
        l->size--;

        if (l->size <= 1){
            l->last = l->head;
        }
        return valor;
    }
}
