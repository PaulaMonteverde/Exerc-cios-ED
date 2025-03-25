#include "forward_list.h"
#include <stdio.h>
#include <stdlib.h>

ForwardList *forward_list_construct(){
    ForwardList *fw = (ForwardList*) calloc(1, sizeof(ForwardList));
    fw->head = NULL;
    fw->size = 0;
    return fw;
}

int forward_list_size(ForwardList *l){
    return l->size;
}

void forward_list_push_front(ForwardList *l, data_type data){
    
    if(l->head == NULL){
        l->head = node_construct(data, NULL);
        l->size++;
    }else {
        Node *aux = NULL;
        aux = l->head;
        l->head = node_construct(data, aux);
        l->size++;
    }
}
void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){
    
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

data_type forward_list_pop_front(ForwardList *l){
    if (l->head == NULL){
        printf("ERRO\n");
        return 0;
    }else {
        data_type valor;
        Node* aux;
        aux = l->head;
        valor = l->head->value;
        l->head = l->head->next;
        node_destroy(aux);
        l->size--;
        return valor;
    }
}

void forward_list_destroy(ForwardList *l){
    
    Node* n = l->head;
    
    while (n != NULL){
        Node* next = n->next;
        node_destroy(n);
        n = next;
    }

    free(l);
}

