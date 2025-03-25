#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Vector* vector_construct(){
    Vector *v;
    v = (Vector*)calloc(1, sizeof(Vector));
    v->allocated = 3;
    v->size = 0;
    v->data = (int*)calloc(v->allocated, sizeof(int));

    return v;

}
void vector_destroy(Vector *v){
    if (v != NULL){
        if (v->data != NULL){
            free(v->data);
        }

        free(v);
    }
}

void vector_push_back(Vector *v, data_type val){

    if (v->allocated == v->size){
        v->allocated = v->allocated*2;
        v->data = (data_type*)realloc(v->data, v->allocated * sizeof(data_type));    
    }
        v->data[v->size] = val;
        v->size++;
    
}

data_type vector_get(Vector *v, int i){
    if (i > v->size){
        printf ("ERRO\n");
        exit(1);
    }else {
        return v->data[i];
    }
}

void vector_set(Vector *v, int i, data_type val){
    if (i > v->size){
        printf ("ERRO\n");
        exit(1);
    }else {
        v->data[i] = val;
    }
}

int vector_size(Vector *v){
    return v->size;
}

int vector_find(Vector *v, data_type val){
    for (int i=0; i< v->size; i++){
        if (vector_get(v,i) == val){
            return i;
        }
    }
    return -1;
}

// Retorna o maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_max(Vector *v){
    
    data_type maior;
    maior = v->data[0];

    for (int i=0; i<v->size; i++){
        if (maior < v->data[i]){
            maior = v->data[i];
        }
    }
    return maior;

}

// Retorna o menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_min(Vector *v){
    
    data_type menor;
    menor = v->data[0];

    for (int i=0; i<v->size; i++){
        if (menor > v->data[i]){
            menor = v->data[i];
        }
    }
    return menor;

}

// Retorna o índice do maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmax(Vector *v){

    data_type maior;
    int cont = 0;
    maior = v->data[0];

    for (int i=0; i<v->size; i++){
        if (maior < v->data[i]){
            maior = v->data[i];
            cont = i;
        }
    }
    return cont;
}

// Retorna o índice do menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmin(Vector *v){

    data_type menor;
    int cont=0;
    menor = v->data[0];

    for (int i=0; i<v->size; i++){
        if (menor > v->data[i]){
            menor = v->data[i];
            cont = i;
        }
    }
    return cont;
}

data_type vector_remove(Vector *v, int i){
    
    vector_get(v,i);

    data_type removido = v->data[i];
    
    for (int j=i; j < v->size; j++){
        v->data[j] = v->data[j+1];
    }

    v->size--;

    return removido;

}
