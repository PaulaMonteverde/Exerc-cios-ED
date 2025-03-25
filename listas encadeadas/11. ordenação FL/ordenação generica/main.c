#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "forward_list.h"

void print_data(data_type data)
{
    printf("%d\n", *(int*)data);
}

int main()
{
    int n, val;

    ForwardList *l = forward_list_construct();

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        int *ptr = malloc(sizeof(int));
        *ptr = val;
        forward_list_push_front(l, ptr);
    }
    forward_list_sort(l);
    forward_list_print(l, print_data);
    forward_list_destroy(l);

    return 0;
}