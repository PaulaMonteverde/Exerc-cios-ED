#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main(){

    int n;
    int value;
    scanf ("%d", &n);

    Node *head = NULL;
    Node *aux = NULL;

    for (int i=0; i<n; i++){
        scanf("%d", &value);
        Node *no = node_construct(value, head);
        head = no;
    }

    while (head != NULL)
    {
        printf("%d\n", node_value(head));
        aux = node_next(head);
        node_destroy(head);
        head = aux;
    }
    
    
    return 0;
}