
#include <stdio.h>
#include <string.h>

#include "vector.h"

int main()
{
    int i, m, idx, val;

    Vector *v;

    v = vector_construct();

    scanf("%d", &m);

    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &idx, &val);
        vector_insert(v, idx, val);
        //printf ("%d",vector_size(v));
    }

    for (i = 0; i < vector_size(v); i++)
        printf("%d\n", vector_get(v, i));

    vector_destroy(v);

    return 0;
}
