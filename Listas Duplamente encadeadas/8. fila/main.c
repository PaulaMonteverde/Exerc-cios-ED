#include "queue.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    Queue *q = queue_construct();
    char command[20], value[100];

    for (int i = 0; i < n; i++) {
        scanf("%s", command);
        if (strcmp(command, "ENQUEUE") == 0) {
            scanf("%s", value);
            char *data = strdup(value);
            queue_push(q, data);
        } else if (strcmp(command, "DEQUEUE") == 0) {
            char *deqValue = (char *)queue_pop(q);
            if (deqValue) {
                printf("%s\n", deqValue);
                free(deqValue);
            }
        }
    }

    queue_destroy(q);
    return 0;
}