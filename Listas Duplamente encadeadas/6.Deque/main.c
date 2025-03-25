#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

int main() {
    int n, value;
    char operation[15];
    Deque *d = deque_construct();
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", operation);
        if (strcmp(operation, "PUSH_FRONT") == 0) {
            scanf ("%*c");
            scanf("%d", &value);
            deque_push_front(d, value);
        } else if (strcmp(operation, "PUSH_BACK") == 0) {
            scanf ("%*c");
            scanf("%d", &value);
            deque_push_back(d, value);
        } else if (strcmp(operation, "POP_FRONT") == 0) {
            printf("%d\n", deque_pop_front(d));
        } else if (strcmp(operation, "POP_BACK") == 0) {
            printf("%d\n", deque_pop_back(d));
        }
    }
    deque_destroy(d);
    return 0;
}
