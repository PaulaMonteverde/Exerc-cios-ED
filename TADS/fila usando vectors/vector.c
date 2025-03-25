#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Vector *vector_construct(int t_alocado){
    Vector *v = (Vector *)calloc(1, sizeof(Vector));
    v->data = (void**)calloc(4, sizeof(void*));
    v->tamanho = 0;
    v->t_alocado = 4;
    return v;
}

void vector_destroy(Vector *v){
    if(v){
        free(v->data);
        free(v);
    }
}

void vector_push_back(Vector *v, void *item){

    if (v->t_alocado == v->tamanho){
        v->t_alocado = v->t_alocado*2;
        v->data = (void**)realloc(v->data, v->t_alocado * sizeof(void**));    
    }
        v->data[v->tamanho] = item;
        v->tamanho++;
}

void *vector_get(Vector *v, int idx){
    if (idx > v->tamanho){
        printf ("ERRO\n");
        exit(1);
    }else {
        return v->data[idx];
    }
}

void* vector_pop_front(Vector *v){
    if (v->tamanho == 0){
        return NULL;
    }
    void* removido = v->data[0];
    for(int i=0; i<v->tamanho-1; i++){
        v->data[i] = v->data[i+1];
    }

    v->tamanho--;

    return removido;
}

int vector_size(Vector *v){
    return v->tamanho;
}
