#include "hash.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HashTable
{
    List **buckets;
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

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn){
    
    HashTable *h = (HashTable*)calloc(1, sizeof(HashTable));

    h->buckets = (List**)calloc(table_size, sizeof(List*)); // aloca espaço dos buckets da hash;
    h->size = table_size;
    h->num_elements = 0;
    h->hash_fn = hash_fn;
    h->cmp_fn = cmp_fn;

    return h;
}

void *hash_table_set(HashTable *h, void *key, void *val){

    int index = h->hash_fn(h, key) % h->size;  //calcula o indice inicial onde a chave tem que ser inserida, ou seja, onde começa;

    if (h->buckets[index] == NULL){
        h->buckets[index] = list_construct();
    }
        
        Node *n = h->buckets[index]->head;   //começa da cabeça;
        

        while(n!=NULL){     //se a cabeça n for nula, percorre a lista, até achar a chave;

            HashTableItem *item = (HashTableItem*)n->value;

            if (h->cmp_fn(item->key, key)==0){      //achou a chave, att o valor;

                void* old_value = item->val;    //guarda o valor antigo para ser retornado;
                item->val = val;                //att o valor;
                return old_value;
            }
            
            n = n->next;                       // se não achar a chave, vai para o próximo nó;
        }

        // se saiu do while sem att valor é porque a chave é inexistente;
        //se é uma nova chave, então precisamos alocar item dinamicamente, quando é o caso de atualizar o calor n precisamos pois pressupõe-se que a memoria do item ja foi alocada;


        HashTableItem *item = (HashTableItem*)calloc(1, sizeof(HashTableItem));    //aloca memoria dinamicamente
        item->key = key;
        item->val = val;

        list_push_front(h->buckets[index], item);                   //insere na lista do bucket da posição indicada pela função hash;

        h->num_elements++;                                          // aumenta o n de elementos;

    return NULL;
}

void *hash_table_get(HashTable *h, void *key){
    
    int index = h->hash_fn(h, key) % h->size;
    
        if (h->buckets[index] == NULL){
            return NULL;
        }else{

            Node *n = h->buckets[index]->head;
            while(n != NULL){
                HashTableItem *item = (HashTableItem*)n->value;
                
                if (h->cmp_fn(item->key, key)==0){
                    return item->val;   
                }

                n = n->next;
            }
            
        }

    return NULL;
}

void *hash_table_pop(HashTable *h, void *key);

int hash_table_size(HashTable *h){
    return h->size;
}
int hash_table_num_elems(HashTable *h){
    return h->num_elements;
}
void hash_table_destroy(HashTable *h){
   //primeiro temos que liberar a chave e o valor dos itens,  os itens das listas, as  listas de cada bucket, depois os buckets e depois a hash_table;
   for (int i=0; i<h->size; i++){
    
    if (h->buckets[i] != NULL){
        
        Node* n = h->buckets[i]->head;
        
        while (n != NULL){      //libera todos os itens da lista do bucket;
            HashTableItem *item = (HashTableItem*)n->value;
            free(item->key);
            free(item->val);
            free(item);
            n = n->next;
        }

        list_destroy(h->buckets[i]);    //libera a lista de itens;
    }

   }

   free(h->buckets);
   free(h);

}

