
#include <stdio.h>
#include <string.h>

#include "vector.h"

int main()
{
    int i, m, n, idx_1, idx_2, val;

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
        scanf("%d %d", &idx_1, &idx_2);
        vector_swap(v, idx_1, idx_2);
    }

    for (i = 0; i < vector_size(v); i++)
        printf("%d\n", vector_get(v, i));

    vector_destroy(v);

    return 0;
}
