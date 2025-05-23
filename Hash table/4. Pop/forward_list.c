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
    //printf("[");

    while(atual != NULL){
        if (atual != NULL){
            print_fn(atual->value);
            // if(atual->next != NULL){
            //     printf(", ");
            // }
        }
        atual = atual->next;
    }
    //printf("]\n");

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

data_type forward_list_get(ForwardList *l, int i){
    if (i>-1 && i<l->size){
        int cont=0;
        Node* atual;
        atual = l->head;
        while(cont<i){
            atual = atual->next;
            cont++;
        }

        return atual->value;
    }else{
        return 0;
    }
}

void forward_list_remove(ForwardList *l, data_type val){
    if (l == NULL || l->head == NULL){
        printf("ERRO\n");
        return;
    }

    Node* atual = l->head;
    Node* anterior = NULL;

    while(atual!= NULL){
        //verifica se o valor é igual ao procurado
        if (atual->value == val){
            
            if (anterior == NULL){
                //o node que vai ser removido é a cabeça;
                l->head = atual->next;
            }else {
                //o node esta no meio da lista;
                anterior->next = atual->next;
            }
            //destruir o nó removido;
            Node *deletado = atual;
            atual = atual->next;
            node_destroy(deletado);
            //diminui o tamanho;
            l->size--;
        }else{
            //move sobre os nós;
            anterior = atual;
            atual = atual->next;

        }

    }
}

void forward_list_cat(ForwardList *l, ForwardList *m){
    
    Node* no = m->head;
    while(no != NULL){
        forward_list_push_front(l, no->value);
        no = no->next;
    }
}
void forward_list_clear(ForwardList *l){
    int tamanho = l->size;
    for (int i=0; i< tamanho; i++){
        forward_list_pop_front(l);
    }
}

ForwardList *forward_list_reverse(ForwardList *l){
    ForwardList *fw = forward_list_construct();
    Node *no = l->head;
    while(no != NULL){
        forward_list_push_front(fw, no->value);
        no = no->next;
    }
    return fw;
}

data_type forward_list_pop_index(ForwardList *l, int index){
    //primeiro passo: validar o indice;
    if (index< 0 || index>= l->size){
        return NULL;
    }else{
        Node* atual = l->head;
        Node* anterior = NULL;
        //segundo passo: fazer caso o indice a ser retirado seja a cabeça (indice 0);
        if (index == 0){
            l->head = atual->next;
            data_type removido = atual->value;
            free(atual);
            l->size--;
            return removido;
        }

        //terceiro passo: fazer um looping que vá até o nó que está no indice desejado
        int i=0;
        while(i < index){
            anterior = atual;
            atual = atual->next;
            i++;
        }

        anterior->next = atual->next;
        data_type removido = atual->value;
        free(atual);
        l->size--;
        return removido;

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


