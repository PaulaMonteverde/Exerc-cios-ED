#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

int cmp_fn(void *key1, void *key2)
{
    int *v = key1;
    int *w = key2;

    return *v - *w;
}

void key_destroy_fn(void *key)
{
    free(key);
}

void val_destroy_fn(void *val)
{
    free(val);
}

int *new_int(int value)
{
    int *ptr = malloc(sizeof(int));
    *ptr = value;
    return ptr;
}

int main()
{
    BinaryTree *bt = binary_tree_construct(cmp_fn, key_destroy_fn, val_destroy_fn);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int val;
        scanf("%d", &val);
        binary_tree_add(bt, new_int(val), new_int(val));
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        KeyValPair *kvp_max = binary_tree_pop_max(bt);  //as funções de pop, como retornam um par chave-valor, devem ser liberadas manualmente na main
        printf("max: %d\n", *(int *)kvp_max->value);
        free(kvp_max->key);
        free(kvp_max->value);
        key_val_pair_destroy(kvp_max);
    }

    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        KeyValPair *kvp_max = binary_tree_pop_max(bt);  //as funções de pop, como retornam um par chave-valor, devem ser liberadas manualmente na main
        KeyValPair *kvp_min = binary_tree_pop_min(bt); 
        printf("min: %d\n", *(int *)kvp_min->value);

        free(kvp_min->key);
        free(kvp_min->value);
        key_val_pair_destroy(kvp_min);
    }

    binary_tree_destroy(bt);

    return 0;
}
