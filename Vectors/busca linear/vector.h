
#ifndef _DATA_STRUCTURES_VECTOR_H_
#define _DATA_STRUCTURES_VECTOR_H_

typedef int data_type;

typedef struct
{
    data_type *data;
    int size;
    int allocated;
} Vector;

Vector *vector_construct();

void vector_push_back(Vector *v, data_type val);

data_type vector_get(Vector *v, int i);
void vector_set(Vector *v, int i, data_type val);
int vector_size(Vector *v);

int vector_find(Vector *v, data_type val);

void vector_destroy(Vector *v);

#endif
