
#include <stdio.h>

#include "list.h"

void print_int(int data)
{
    printf("%d", data);
}

int main()
{
    int n, val;

    List *l = list_construct();

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        list_push_front(l, val);
    }

    // test the size and print functions
    printf("Size: %d\n", list_size(l));
    printf("Lista: ");
    list_print(l, print_int);
    printf("\n");

    // test the destroy function
    list_destroy(l);

    return 0;
}