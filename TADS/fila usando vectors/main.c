#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    Queue *fila = queue_construct();
    char comando[10];
    int n;
    scanf("%d", &n);
    scanf("%*c");

    for (int i=0; i<n; i++){
        scanf("%s", comando);

        if (strcmp(comando, "ENQUEUE") == 0){

            char *item = (char*) calloc(50, sizeof(char)); 
            scanf(" %s", item);
            queue_enqueue(fila, item);

        }else if(strcmp(comando, "DEQUEUE") == 0){
            
            char* item_rmvd = (char*)queue_dequeue(fila);
            if (item_rmvd){
                printf("%s\n", item_rmvd);
                free(item_rmvd);
            }
        }
    }

    queue_destruct(fila);
    return 0;
}