

#include <stdio.h>
#include <stdlib.h>
#include "product.h"

Product *create_product()
{
    char name[128];
    float price;
    int qtd;

    scanf("%[^\n]\n", name);
    scanf("%f", &price);
    scanf("%d", &qtd);

    return product_constructor(name, price, qtd);
}

void perform_operation(Product *product)
{
    char name[128];
    float price, discount;
    int qtd;
    char operation;

    scanf("\n%c", &operation);

    if (operation == 'P')
        product_print(product);
    else if (operation == 'S')
    {
        scanf("\n%d", &qtd);
        product_sell(product, qtd);
    }
    else if (operation == 'B')
    {
        scanf("\n%d", &qtd);
        product_buy(product, qtd);
    }
    else if (operation == 'D')
    {
        scanf("\n%f", &discount);
        product_set_discount(product, discount);
    }
    else if (operation == 'Q')
    {
        scanf("\n%f", &price);
        product_set_price(product, price);
    }
    else if (operation == 'N')
    {
        scanf("\n%[^\n]\n", name);
        product_set_name(product, name);
    }
    else
        printf("Operacao invalida.\n");
}

int main()
{
    Product *product = create_product();

    int n_operations;
    scanf("%d", &n_operations);

    // for (int i = 0; i < n_operations; ++i)
    //     perform_operation(product);

    product_destructor(product);

    return 0;
}
