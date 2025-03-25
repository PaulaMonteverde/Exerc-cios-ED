#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "vector.h"

int hash_str(HashTable *h, void *data) {
    char *str = (char *)data;
    long hash_val = 0;
    int base = 127;

    for (size_t i = 0; i < strlen(str); i++)
        hash_val = (base * hash_val + str[i]) % hash_table_size(h);

    return hash_val;
}

int cmp_str(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

int cmp_vector(const void *a, const void *b) {
    HashTableItem *item1 = (HashTableItem*) a;
    HashTableItem *item2 = (HashTableItem*) b;

    return strcmp((char*)item1->key, (char*)item2->key);
}



int main() {
    int n;
    scanf("%d", &n);  

    HashTable * word_counter = hash_table_construct(11, hash_str, cmp_str);

    for (int i = 0; i < n; i++) {
        char word[100];
        scanf("%s", word);

        int *freq = (int *)hash_table_get(word_counter, word);
        if (freq) {
            //se ja existe na tabela, incrementa;
            (*freq)++;
        } else {
            int *new_freq = (int *)malloc(sizeof(int));
            *new_freq = 1;
            hash_table_set(word_counter, strdup(word), new_freq);
        }
    }

    Vector *v = hash_to_vector(word_counter);

    vector_sort(v, cmp_vector);

    for (int i = 0; i < vector_size(v); i++) {
        HashTableItem *item = (HashTableItem *)vector_get(v, i);
        printf("%s %d\n", (char *)item->key, *(int *)item->val);
    }

    vector_destroy(v);
    hash_table_destroy(word_counter);

    return 0;
}