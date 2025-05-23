#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "forward_list.h" 

struct HashTable {
    ForwardList **buckets;
    int size;
    int num_elements;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
};

typedef struct HashTableIterator{
    HashTable* table;
    int current_bucket;
    ListIterator *list_iterator;
    int valid;
} HashTableIterator;

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = table_size;
    h->num_elements = 0;
    h->hash_fn = hash_fn;
    h->cmp_fn = cmp_fn;
    
    h->buckets = (ForwardList **)calloc(table_size, sizeof(ForwardList *));
    for (int i = 0; i < table_size; i++) {
        h->buckets[i] = forward_list_construct();
    }
    
    return h;
}

HashTableItem* hash_create_pair(const void* key, void* value) {
    HashTableItem* pair = (HashTableItem*)malloc(sizeof(HashTableItem));
    pair->key = (void*)key;
    pair->val = value;
    return pair;
}

// Função para inserção/atualização de pares chave-valor em O(1)
void *hash_table_set(HashTable *h, void *key, void *val) {
    int hash_idx = h->hash_fn(h, key) % h->size;
    ForwardList *bucket = h->buckets[hash_idx];
    
    // Procura a chave no bucket
    ListIterator *it = list_iterator_construct(bucket);
    HashTableItem *item;
    while (!list_iterator_is_over(it)) {
        data_type *data_ptr = list_iterator_next(it);
        if (data_ptr != NULL) {
            item = (HashTableItem *)(*data_ptr);
            if (h->cmp_fn(item->key, key) == 0) {
                // Chave encontrada, atualiza o valor
                void *old_val = item->val;
                item->val = val;
                list_iterator_destroy(it);
                return old_val;
            }
        }
    }
    list_iterator_destroy(it);
    
    // Chave não encontrada, cria um novo item e adiciona ao bucket
    HashTableItem *new_item = hash_create_pair(key, val);
    forward_list_push_front(bucket, (data_type)new_item);
    h->num_elements++;
    return NULL;
}

void *hash_table_get(HashTable *h, void *key) {
    int hash_idx = h->hash_fn(h, key) % h->size;
    ForwardList *bucket = h->buckets[hash_idx];
    
    // Procura a chave no bucket
    ListIterator *it = list_iterator_construct(bucket);
    HashTableItem *item;
    
    while (!list_iterator_is_over(it)) {
        data_type *data_ptr = list_iterator_next(it);
        if (data_ptr != NULL) {
            item = (HashTableItem *)(*data_ptr);
            if (h->cmp_fn(item->key, key) == 0) {
                // Chave encontrada
                list_iterator_destroy(it);
                return item->val;
            }
        }
    }
    list_iterator_destroy(it);
    
    // Chave não encontrada
    return NULL;
}

void *hash_table_pop(HashTable *h, void *key) {
    int hash_idx = h->hash_fn(h, key) % h->size;
    ForwardList *bucket = h->buckets[hash_idx];
    
    // Caso especial: bucket vazio
    if (forward_list_size(bucket) == 0) {
        return NULL;
    }
    
    // Verificamos o primeiro elemento separadamente
    HashTableItem *first_item = (HashTableItem *)forward_list_get(bucket, 0);
    if (h->cmp_fn(first_item->key, key) == 0) {
        void *val = first_item->val;
        forward_list_pop_front(bucket);
        free(first_item);
        h->num_elements--;
        return val;
    }
    
    // Percorre a lista para encontrar o item (começando do segundo elemento)
    for (int i = 1; i < forward_list_size(bucket); i++) {
        HashTableItem *item = (HashTableItem *)forward_list_get(bucket, i);
        if (h->cmp_fn(item->key, key) == 0) {
            void *val = item->val;
            // Usando a função forward_list_pop_index para remover o item
            forward_list_pop_index(bucket, i);
            free(item);
            h->num_elements--;
            return val;
        }
    }
    
    // Chave não encontrada
    return NULL;
}

// Número de buckets
int hash_table_size(HashTable *h) {
    return h->size;
}

// Número de elementos inseridos
int hash_table_num_elems(HashTable *h) {
    return h->num_elements;
}

// Libera o espaço alocado para a tabela hash
void hash_table_destroy(HashTable *h) {
    for (int i = 0; i < h->size; i++) {
        ForwardList *bucket = h->buckets[i];
        
        // Precisamos liberar cada par chave-valor na lista
        while (forward_list_size(bucket) > 0) {
            HashTableItem *item = (HashTableItem *)forward_list_pop_front(bucket);
            free(item->key);  // Libera a chave (nome)
            free(item->val);  // Libera o valor (idade)
            free(item);       // Libera o item em si
        }
        
        forward_list_destroy(bucket);
    }
    
    free(h->buckets);
    free(h);
}

// Cria um novo iterador para a tabela hash
HashTableIterator *hash_table_iterator(HashTable *h) {
    HashTableIterator *it = (HashTableIterator *)malloc(sizeof(HashTableIterator));
    it->table = h;
    it->current_bucket = 0;
    it->valid = 0;
    
    // Encontra o primeiro bucket não vazio
    while (it->current_bucket < h->size) {
        ForwardList *bucket = h->buckets[it->current_bucket];
        if (forward_list_size(bucket) > 0) {
            it->list_iterator = list_iterator_construct(bucket);
            it->valid = 1;
            break;
        }
        it->current_bucket++;
    }
    
    return it;
}

// Retorna 1 se o iterador chegou ao fim da tabela hash ou 0 caso contrário
int hash_table_iterator_is_over(HashTableIterator *it) {
    return !it->valid;
}

// Retorna o próximo par chave valor da tabela hash
HashTableItem *hash_table_iterator_next(HashTableIterator *it) {
    if (!it->valid) {
        return NULL;
    }
    
    // Obtém o item atual
    data_type *data_ptr = list_iterator_next(it->list_iterator);
    if (data_ptr == NULL) {
        // Não deveria acontecer se valid for true, mas é uma verificação extra
        it->valid = 0;
        return NULL;
    }
    
    HashTableItem *current_item = (HashTableItem *)(*data_ptr);
    
    // Verifica se chegamos ao fim do bucket atual
    if (list_iterator_is_over(it->list_iterator)) {
        // Libera o iterador atual
        list_iterator_destroy(it->list_iterator);
        
        // Procura o próximo bucket não vazio
        it->current_bucket++;
        while (it->current_bucket < it->table->size) {
            ForwardList *bucket = it->table->buckets[it->current_bucket];
            if (forward_list_size(bucket) > 0) {
                it->list_iterator = list_iterator_construct(bucket);
                return current_item;
            }
            it->current_bucket++;
        }
        
        // Não há mais buckets
        it->valid = 0;
    }
    
    return current_item;
}

// Desaloca o iterador da tabela hash
void hash_table_iterator_destroy(HashTableIterator *it) {
    if (it->valid) {
        list_iterator_destroy(it->list_iterator);
    }
    free(it);
}
