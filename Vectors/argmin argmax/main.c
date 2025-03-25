
#include <stdio.h>
#include <string.h>

#include "vector.h"

int main()
{
    int m, val;

    Vector *v;

    v = vector_construct();

    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &val);
        vector_push_back(v, val);
    }

    printf("%d\n", vector_max(v));
    printf("%d\n", vector_min(v));
    printf("%d\n", vector_argmax(v));
    printf("%d\n", vector_argmin(v));

    vector_destroy(v);

    return 0;
}
