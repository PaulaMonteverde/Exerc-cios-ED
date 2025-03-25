#include "hash.h"
#include "forward_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HashTable
{
    ForwardList **buckets;
    int size;
    int num_elements;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
};

struct HashTableIterator
{
    HashTable *hash_table;
    int index;
};

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{

    HashTable *h = (HashTable *)calloc(1, sizeof(HashTable));

    h->buckets = (ForwardList **)calloc(table_size, sizeof(ForwardList *)); // aloca espaço dos buckets da hash;
    h->size = table_size;
    h->num_elements = 0;
    h->hash_fn = hash_fn;
    h->cmp_fn = cmp_fn;

    return h;
}

void *hash_table_set(HashTable *h, void *key, void *val)
{

    int index = h->hash_fn(h, key) % h->size; // calcula o indice inicial onde a chave tem que ser inserida, ou seja, onde começa;

    if (h->buckets[index] == NULL) // se for um bucket nunca acessado antes, constroi uma lista;
    {
        h->buckets[index] = forward_list_construct();
    }

    Node *atual = h->buckets[index]->head; // começa da cabeça;

    while (atual != NULL)
    { // se a cabeça n for nula, percorre a lista, até achar a chave;

        HashTableItem *item = (HashTableItem *)atual->value;

        if (h->cmp_fn(item->key, key) == 0)
        { // achou a chave, att o valor;

            void *old_value = item->val; // guarda o valor antigo para ser retornado;
            item->val = val;             // att o valor;
            return old_value;
        }

        atual = atual->next; // se não achar a chave, vai para o próximo nó;
    }

    // se saiu do while sem att valor é porque a chave é inexistente;
    // se é uma nova chave, então precisamos alocar item dinamicamente, quando é o caso de atualizar o calor n precisamos pois pressupõe-se que a memoria do item ja foi alocada;

    HashTableItem *item = (HashTableItem *)calloc(1, sizeof(HashTableItem)); // aloca memoria dinamicamente
    item->key = key;
    item->val = val;

    forward_list_push_front(h->buckets[index], item); // insere na lista do bucket da posição indicada pela função hash;

    h->num_elements++; // aumenta o n de elementos;

    return NULL;
}

void *hash_table_get(HashTable *h, void *key)
{

    int index = h->hash_fn(h, key) % h->size;

    if (h->buckets[index] == NULL)
    {
        return NULL;
    }
    else
    {

        Node *atual = h->buckets[index]->head;
        while (atual != NULL)
        {
            HashTableItem *item = (HashTableItem *)atual->value;

            if (h->cmp_fn(item->key, key) == 0)
            {
                return item->val;
            }

            atual = atual->next;
        }
    }

    return NULL;
}

void *hash_table_pop(HashTable *h, void *key)
{
    int index = h->hash_fn(h, key) % h->size; // encontra o indice do bucket;

    if (h->buckets[index] == NULL || h->buckets[index]->head == NULL) // verifica se o indice é NULL, para n dar double free;
    {
        return NULL;
    }

    Node *atual = h->buckets[index]->head; // defino um nó atual para percorrer a lista a partir dele;
    int cont = 0;                          // preciso de um contador para o index da chave a ser rem

    while (atual != NULL) // eqnt atual não for NULL;
    {
        HashTableItem *item = (HashTableItem *)atual->value; // crio um item para fazer as comparações necessárias com as chaves;

        if (h->cmp_fn(item->key, key) == 0)
        {
            // void *removido = item->val;          // não preciso disso pois FL_pop_index ja retorna o removido;

            HashTableItem *removido = forward_list_pop_index(h->buckets[index], cont); // h->buckets[index] é a lista!

            void* valor_removido = removido->val;
            free(removido->key);
            free(removido);
            
            h->num_elements--;
            return valor_removido;
        }

        atual = atual->next;
        cont++;
    }

    return NULL;
}

int hash_table_size(HashTable *h)
{
    return h->size;
}

int hash_table_num_elems(HashTable *h)
{
    return h->num_elements;
}

void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->size; i++)
    {
        if (h->buckets[i] != NULL)
        {
            Node *n = h->buckets[i]->head;
            while (n != NULL)
            {
                Node *next = n->next;
                HashTableItem *item = (HashTableItem *)n->value;

                free(item->key);
                free(item->val); // Se precisar liberar o valor também
                free(item);
                free(n); // Libera o nó da lista

                n = next;
            }
            free(h->buckets[i]); // Libera o próprio bucket
        }
    }
    free(h->buckets);
    free(h);
}
