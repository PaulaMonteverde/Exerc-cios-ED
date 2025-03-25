#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash2(const char *str, int base, int table_size){
    int string_size = strlen(str);
    unsigned long long hash_value = 0;

    for(int i = 0; i<string_size; i++){
        hash_value = (hash_value * base + str[i]) % table_size;
    }

    return hash_value;
}

int main(){
    int base, n_strings, table_size;

    scanf("%d %d %d", &base, &n_strings, &table_size);
    
    for (int i=0; i<n_strings; i++){
        char str[100];
        scanf("%s", str);
        unsigned long hash_value = hash2(str, base, table_size);
        printf("%lu\n", hash_value);
    }
    
    return 0;
}