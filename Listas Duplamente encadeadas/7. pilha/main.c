#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define MAX_STR 100

int main() {
    int n;
    char command[MAX_STR];

    Stack *stack = stack_construct();

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", command);

        if (strcmp(command, "PUSH") == 0) {
            char *str = (char *)malloc(MAX_STR * sizeof(char));
            scanf("%s", str);
            stack_push(stack, str);
        } else if (strcmp(command, "POP") == 0) {
            char *popped = (char *)stack_pop(stack);
            if (popped) {
                printf("%s\n", popped);
                free(popped);  // Liberando a string removida
            }
        }
    }

    stack_destroy(stack);  // Liberando memória ao final

    return 0;
}
