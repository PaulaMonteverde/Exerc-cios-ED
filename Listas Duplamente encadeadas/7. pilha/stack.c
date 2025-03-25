#include "stack.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{
    Node *topo;
    int size;
}Stack;

Stack *stack_construct(){
    Stack *s = (Stack*)calloc(1, sizeof(Stack));
    s->topo = NULL;
    s->size = 0;
    return s;
}
void stack_destroy(Stack *s){
    Node* atual = s->topo;
    
    while(atual != NULL){ // sempre colocar o nó que guarda o topo e não o s->topo
        Node *aux = atual;
        atual = atual->prev; // em pilha é passar para o prev, não next;
        free(aux->value); //tem que liberar a string;
        node_destroy(aux);
    }

    free(s);
}
int stack_size(Stack *s){
    return s->size;
}
void stack_push(Stack *s, void *data){
    
    Node* novo_no = node_construct(data, s->topo, NULL);
    
    if (s->topo == NULL){
        s->topo = novo_no;
    }else{
        s->topo->next = novo_no;
        s->topo = novo_no;
    }

    s->size++;
}
void* stack_pop(Stack *s){
    
    data_type valor; 
    
    if (s->topo != NULL){
        Node* aux = s->topo;
        valor = s->topo->value;
        s->topo = s->topo->prev;
        if (s->topo != NULL){
            s->topo->next = NULL;
        }
        node_destroy(aux);
        s->size--;
    }

    return valor;
}
