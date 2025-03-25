#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

struct vector {
    void** data;
    int size;
    int allocated;
};

Vector* vector_construct(){
    Vector *v = (Vector*)calloc(1, sizeof(Vector));
    v->data = (void**)calloc(4, sizeof(void*));
    v->size =0;
    v->allocated = 4;
    return v;
}

void vector_push_back(Vector *v, void *item){
    if (v->allocated == v->size){
        v->allocated = v->allocated*2;
        v->data = (void**)realloc(v->data, v->allocated * sizeof(void**));    
    }
        v->data[v->size] = item;
        v->size++;
}

void* vector_pop_back(Vector *v){
    if (v->size == 0){
        return NULL;
    }
    void* removido = v->data[v->size-1];
    v->data[v->size-1] = NULL;
    v->size--;
    return removido;
}

int vector_size(Vector *v){
    return v->size;
}



void vector_swap(Vector *v, int p1, int p2){
    void* aux = v->data[p1];
    v->data[p1] = v->data[p2];
    v->data[p2] = aux;
}

void *vector_get(Vector *v, int idx){
    if (idx > v->size){
        printf ("ERRO vector get\n");
        exit(1);
    }else {
        return v->data[idx];
    }
}

void vector_set(Vector *v, int idx, void* item){
    if (idx > v->size){
        printf ("ERRO vector set\n");
        exit(1);
    }else {
        v->data[idx] = item;
    }
}
void* vector_max(Vector *v){
    void* maior;
    maior = v->data[0];
    
    for ( int i=0; i<v->size; i++){
        if (maior < v->data[i]){
            maior = v->data[i];
        }
    }
    return maior;

}
int vector_argmax(Vector *v, int cmp_fn(const void *, const void *)){
    void* maior;
    maior = v->data[0];
    int cont =0;
    
    for (int i=1; i<v->size; i++){
        void* atual = vector_get(v, i);
        
        if (cmp_fn(atual, maior) > 0){
            maior = atual;
            cont = i;
        }
    }
    return cont;
}

void* vector_remove(Vector *v, int idx){
    void* removido = v->data[idx];
    for (int i = idx; i <v->size-1; i++){
        v->data[i] = v->data[i+1];
    }

    v->size--;
    return removido;
}

void vector_destroy(Vector *v){
    if(v){
        free(v->data);
        free(v);
    }
}

void vector_print(Vector *v, void (*print_element) (void*))
{
   for (int i = 0; i < v->size; i++) {
        print_element(v->data[i]); 
    }
}


void vector_sort(Vector *v, int (*cmp_fn) (const void*, const void*)){
  for(int i = 0; i < v->size - 1; i++){
    int swap = 0;

    for(int j = 0; j < v->size - i - 1; j++){
      //se o anterior for maior que o próximo, troca;
      if (cmp_fn(v->data[j], v->data[j + 1]) > 0){
        vector_swap(v, j, j + 1);
        swap = 1;
      }
    }

    //verifica se houve troca;
    if(swap == 0){
      break;
    }
  }
}