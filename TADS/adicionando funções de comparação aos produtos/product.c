#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "product.h"

struct product{
    char* nome;
    float price;
    float discount;
    int qtd;
    int sales;
};

Product *product_constructor(const char *name, float price, int qtd){

    if (price <= 0 || qtd < 0) {
        printf("VALOR INVALIDO\n");
        return NULL;
    }
    
    Product *p = (Product*) calloc (1, sizeof(Product));
    if (p ==  NULL){
        exit(printf("ERRO ao alocar produto\n"));
    }

    p->nome = (char*) calloc (64, sizeof(char));
    if (p->nome == NULL){
        free(p);
        exit(printf("ERRO ao alocar nome do produto\n"));
    }

    strncpy(p->nome, name, 63);
    p->nome[63] = '\0';
    p->sales = 0;
    p->discount = 0.0;
    p->price = price;
    p->qtd = qtd;

    return p;

}

const char *product_get_name(Product *product){
    return product->nome;
}
float product_get_price(Product *product){
    return product->price;
}
float product_get_discount(Product *product){
    return product->discount;
}
int product_get_qtd(Product *product){
    return product->qtd;
}
int product_get_sales(Product *product){
    return product->sales;
}

void product_set_name(Product *product, const char *name){
    strncpy(product->nome, name, 63);
    product->nome[63]= '\0';
}

void product_set_price(Product *product, float price){
    if (price > 0){
        product->price = price;
    }else{
        printf ("VALOR INVALIDO\n"); 
    }
}
void product_set_discount(Product *product, float discount){
    if (discount >= 0 && discount <= 1){
        product->discount = discount;
    }else{
        printf ("VALOR INVALIDO\n");
    }
}

void product_sell(Product *product, int quantity){
    if (quantity <= 0){
        printf("QUANTIDADE INVALIDA\n");
    }else{
        if (quantity > product->qtd){
            printf("ESTOQUE INSUFICIENTE\n");
        }else {
            product->qtd -= quantity;
            product->sales += quantity; 
        }
    }
}
void product_buy(Product *product, int quantity){
    if (quantity>0){
        product->qtd += quantity;
    }else {
        printf("QUANTIDADE INVALIDA\n");
    }
}

float product_get_price_with_discount(Product *product){
    return product->price *(1-product->discount);
}

void product_print(Product *product){
    printf("Product(%s, %.2f, %.2f, %.2f, %d, %d)", product->nome, product->price, product->discount, product_get_price_with_discount(product), product->qtd, product->sales);
}

void product_destructor(Product *product){
    if (product != NULL){
        
        if (product->nome != NULL){
            free(product->nome);
        }

        free(product);
    }
}

int product_compare_name(const void *p1, const void *p2){
    
    Product *product1 = *(Product **)p1;
    Product *product2 = *(Product **)p2;
    
    return strcmp(product1->nome, product2->nome);
}

int product_compare_price(const void *p1, const void *p2){
    
    Product *product1 = *(Product **)p1;
    Product *product2 = *(Product **)p2;
    
    if (product1->price < product2->price) return -1;
    if (product1->price > product2->price) return 1;
    
    return 0;

}

int product_compare_sales(const void *p1, const void *p2){
    
    const Product *product1 = *(const Product **)p1;
    const Product *product2 = *(const Product **)p2;

    if (product1->sales < product2->sales) return -1;
    if (product1->sales > product2->sales) return 1;
    return 0; 
}

