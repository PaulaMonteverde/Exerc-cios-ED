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

// Remove o primeiro elemento
data_type vector_pop_front(Vector *v){
    
    data_type removido = v->data[0];
    for(int i=0; i<v->size; i++){
        v->data[i] = v->data[i+1];
    }

    v->size--;

    return removido;

}

// Remove o ultimo elemento
data_type vector_pop_back(Vector *v){
    
    data_type removido = v->data[v->size-1];
    v->data[v->size-1] = 0;
    v->size--;
    return removido;
}

// Insere o elemento na i-esima posicao
void vector_insert(Vector *v, int i, data_type val){
   if (v->size >= v->allocated){
        v->allocated = v->allocated*2;
        v->data = (data_type*) realloc (v->data, v->allocated * sizeof(data_type));
   }

   for (int j = v->size; j > i; j--){
        v->data[j] = v->data[j-1];
   }

   v->data[i] = val;
   v->size++;
}

void vector_swap(Vector *v, int i, int j){
    data_type aux; 
    aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}

// Ordena o vetor in-place (sem criar um novo vetor)
void vector_sort(Vector *v){
    for (int i=1; i<v->size; i++){
        for (int j=0; j<v->size - 1; j++){
            if (v->data[j]> v->data[j+1]){
                data_type aux = v->data[j];
                v->data[j] = v->data[j+1];
                v->data[j+1] = aux;
            }
        }
    }
}

// Retorna o indice de val usando busca binaria. Retorna -1 se nao encontrado.
int vector_binary_search(Vector *v, data_type val){
    int middle;
   
   if (v->size % 2 == 0){
        middle = v->size/2;
   }else {
        middle = (v->size - 1)/2;
   }

    if (v->data[middle] > val){
        for (int i = 0; i < middle; i++){
            if (v->data[i] == val){
                return i;
            }
        }

        return -1;
    }

    if (v->data[middle] < val){
        for (int i = middle+1; i < v->size; i++){
            if (v->data[i] == val){
                return i;
            }
        }

        return -1;
    }

    if (v->data[middle] == val){
        return middle;
    }

    return -1;
}

