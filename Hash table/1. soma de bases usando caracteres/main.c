#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long compute_hash(const char *str, int base){
    int string_size = strlen(str);
    unsigned long long hash_value = 0;
    unsigned long long power = 1;

    for(int i = string_size-1; i>=0; i--){
        hash_value += (str[i]*power);
        power *= base;
    }

    return hash_value;
}

int main(){
    int base, n_strings;

    scanf("%d %d", &base, &n_strings);
    
    for (int i=0; i<n_strings; i++){
        char str[100];
        scanf("%s", str);
        unsigned long long hash_value = compute_hash(str, base);
        printf("%llu\n", hash_value);
    }
    
    return 0;
}