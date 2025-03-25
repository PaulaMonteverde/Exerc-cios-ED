#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    Stack *pilha = stack_construct();
    char comando[10];
    int n;
    scanf("%d", &n);
    scanf("%*c");

    for (int i=0; i<n; i++){
        scanf("%s", comando);

        if (strcmp(comando, "PUSH") == 0){

            char *item = (char*) calloc(50, sizeof(char)); 
            scanf(" %s", item);
            stack_push(pilha, item);

        }else if(strcmp(comando, "POP") == 0){
            
            char* item_rmvd = (char*)stack_pop(pilha);
            if (item_rmvd){
                printf("%s\n", item_rmvd);
                free(item_rmvd);
            }
        }
    }

    stack_destruct(pilha);
    return 0;
}