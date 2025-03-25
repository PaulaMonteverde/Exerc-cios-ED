#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct vector{
    void **data;
    int tamanho;
    int t_alocado;
} Vector;

Vector *vector_construct();
void vector_destroy(Vector *v);
void vector_push_back(Vector *v, void *item);
void *vector_get(Vector *v, int idx);
void vector_sort(Vector *v, int (*cmp_fn)(const void*, const void*));

#endif