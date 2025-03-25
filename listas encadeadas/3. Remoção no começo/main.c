
#include <stdio.h>

#include "forward_list.h"

int main()
{
    int n, val;

    ForwardList *l = forward_list_construct();

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        forward_list_push_front(l, val);
    }

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        printf("%d\n", forward_list_pop_front(l));

    // test the destroy function
    forward_list_destroy(l);

    return 0;
}