#ifndef STACK_H
#define STACK_H

#include "vector.h"

typedef struct stack{
    Vector *v;
} Stack;

Stack* stack_construct();
void stack_destruct(Stack *s);
int stack_size(Stack *s);
void stack_push(Stack *s, void* item);
void* stack_pop(Stack *s);

#endif