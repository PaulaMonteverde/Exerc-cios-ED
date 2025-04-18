#ifndef _VECTOR_H
#define _VECTOR_H

typedef struct vector Vector;

Vector* vector_construct();
void vector_push_back(Vector *v, void *item);
void* vector_pop_back(Vector *v);
int vector_size(Vector *v);
void vector_swap(Vector *v, int p1, int p2);
void *vector_get(Vector *v, int idx);
void vector_set(Vector *v, int idx, void* item);
void* vector_max(Vector *v);
int vector_argmax(Vector *v, int cmp_fn(const void *, const void *));
void* vector_remove(Vector *v, int idx);
void vector_destroy(Vector *v);
void vector_print(Vector *v, void (*print_element) (void*));
void vector_sort(Vector *v, int (*cmp_fn) (const void*, const void*));


#endif