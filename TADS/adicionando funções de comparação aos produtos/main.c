#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

Product *create_product()
{
    char name[128];
    float price;
    int qtd;

    scanf("%*c");
    scanf("%[^\n]\n", name);
    scanf("%f", &price);
    scanf("%d", &qtd);

    return product_constructor(name, price, qtd);
}


int main()
{

    int n_operations;
    int qtd;

    scanf("%d", &n_operations);
    Product *products[n_operations];

    for (int i=0; i<n_operations; i++){
        products[i] = create_product();
        scanf("%d", &qtd);
        product_sell(products[i], qtd);
    }

    char c; 
    scanf (" %c", &c);
    
    if (c == 'N'){
        qsort(products, n_operations, sizeof(Product*), product_compare_name);
    }else if (c == 'P'){
        qsort(products, n_operations, sizeof(Product*), product_compare_price);
    }else if (c == 'S'){
        qsort(products, n_operations, sizeof(Product*), product_compare_sales);
    }

    for (int i =0; i<n_operations; i++){
        product_print(products[i]);
        printf("\n");
    }
    
    for (int i =0; i<n_operations; i++){
        product_destructor(products[i]);
    }

    return 0;
}
