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

