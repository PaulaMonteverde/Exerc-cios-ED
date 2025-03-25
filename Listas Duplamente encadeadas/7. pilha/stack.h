#ifndef _STACK_H
#define _STACK_H

typedef struct Stack Stack;

Stack *stack_construct();
void stack_destroy(Stack *s);
int stack_size(Stack *s);
void stack_push(Stack *s, void *data);
void* stack_pop(Stack *s);


#endif

