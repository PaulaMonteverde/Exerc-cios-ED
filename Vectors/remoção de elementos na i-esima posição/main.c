
#include <stdio.h>
#include <string.h>

#include "vector.h"

int main()
{
    int i, m, n, val, idx;

    Vector *v;

    v = vector_construct();

    scanf("%d %d", &m, &n);

    for (i = 0; i < m; i++)
    {
        scanf("%d", &val);
        vector_push_back(v, val);
    }

    for (i = 0; i < n; i++)
    {
        scanf("%d", &idx);
        vector_remove(v, idx);
    }

    for (i = 0; i < vector_size(v); i++)
        printf("%d\n", vector_get(v, i));

    vector_destroy(v);

    return 0;
}
