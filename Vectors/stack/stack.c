#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* stack_construct(){
    Stack *s = (Stack*)calloc(1, sizeof(Stack));
    s->v = vector_construct();
    return s;
}
int stack_size(Stack *s){
    return vector_size(s->v);
}
void stack_push(Stack *s, void* item){
    vector_push_back(s->v, item);
}
void* stack_pop(Stack *s){
    if (stack_size(s)>0){
        return vector_pop_back(s->v);
    }else{
        return NULL;
    }
}
void stack_destruct(Stack *s){
    while(stack_size(s)>0){
        free(stack_pop(s));
    }
    vector_destroy(s->v);
    free(s);
}