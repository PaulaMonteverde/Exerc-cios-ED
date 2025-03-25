#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

typedef struct Node{
    KeyValPair *pair;
    struct Node *left;
    struct Node *right;
} Node;

struct BinaryTree
{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
    int size;
};


KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *pair = (KeyValPair*)calloc(1, sizeof(KeyValPair));
    pair->key = key;
    pair->value = val;
    return pair;
}

void key_val_pair_destroy(KeyValPair *kvp){
    if (kvp != NULL){
        free(kvp);
    }
}

Node* node_construct(void *key, void *value){
    
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->pair = key_val_pair_construct(key, value);
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    if (node != NULL) {

        if (key_destroy_fn != NULL){
            key_destroy_fn(node->pair->key);
        }
        if (val_destroy_fn != NULL){
            val_destroy_fn(node->pair->value);
        }
        free(node->pair);
        free(node);
    }
}

BinaryTree *binary_tree_construct( CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    BinaryTree *bt = (BinaryTree*)calloc(1, sizeof(BinaryTree));
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;
    bt->cmp_fn = cmp_fn;
    bt->root = NULL;
    bt->size = 0;
    return bt;
}

void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value) {
    if (bt == NULL || key == NULL) return; 
    Node **node = &bt->root;
    
    while (*node) {
        int cmp = bt->cmp_fn(key, (*node)->pair->key);
        if (cmp < 0) {
            node = &(*node)->left;
        } else if (cmp > 0) {
            node = &(*node)->right;
        } else {
            // Se a chave já existe, atualiza o valor
            if (bt->val_destroy_fn != NULL) {
                bt->val_destroy_fn((*node)->pair->value);
            }
            if (bt->key_destroy_fn != NULL){
                bt->key_destroy_fn((*node)->pair->key);
            }
            (*node)->pair->value = value;
            (*node)->pair->key = key;

            return;
        }
    }

    *node = node_construct(key, value);
    bt->size++;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){
    binary_tree_add_recursive(bt, key, value);
}

void *binary_tree_get(BinaryTree *bt, void *key){
    if (bt == NULL || key == NULL){
        return NULL;
    } 

    Node *current = bt->root;

    while(current != NULL){
        int cmp = bt->cmp_fn(key, current->pair->key);
        if (cmp == 0){
            return current->pair->value;
        }else if (cmp < 0){
            current = current->left;
        }else {
            current = current->right;
        }
    }
    return NULL;
}

int binary_tree_empty(BinaryTree *bt) {
    return bt == NULL || bt->root == NULL;
}

void binary_tree_destroy(BinaryTree *bt) {
    if (bt == NULL){
        return;
    } 

    void destroy_nodes(Node *node){
        if (node == NULL){
            return;
        }

        destroy_nodes(node->left);
        destroy_nodes(node->right);

        node_destroy(node, bt->key_destroy_fn, bt->val_destroy_fn);
    }

    destroy_nodes(bt->root);

    free(bt);
}

void binary_tree_remove(BinaryTree *bt, void *key){
    //primeiro passo: encontrar o nó
    if (bt == NULL){
        return;
    }

    Node **current = &bt->root;

    while (current != NULL){
        int cmp = bt->cmp_fn(key, (*current)->pair->key);
        if (cmp == 0){
            //encontrou a chave;
            Node *removed = *current;

            //agr temos que verificar se o nó que queremos remover tem nenhum, um ou dois filhos;
            if (removed->left == NULL && removed->right == NULL){
                //primeiro caso: nenhum filho. só remover;

                *current = NULL;

            }else if(removed->left != NULL && removed->right == NULL){
                //segundo caso: um filho esquerdo, substituir pelo filho;

                *current = removed->left;

            }else if (removed->left == NULL && removed->right != NULL){
                //segundo caso: um filho direito, substituir pelo filho;

                *current = removed->right;

            }else if(removed->left != NULL && removed->right != NULL){
                //terceiro caso: dois filhos, substituir pelo sucessor;
                //achar o sucessor: bt->root->right e dps esquerda até NULL;

                Node **sucessor = &removed->right;
                while ((*sucessor)->left != NULL){
                    sucessor = &(*sucessor)->left;
                }

                //mudar o nó atual com o sucessor;

                KeyValPair *temp = removed->pair;
                removed->pair = (*sucessor)->pair;
                (*sucessor)->pair = temp;

                //remover o sucessor (que agora tem o valor do nó atual);

                removed = *sucessor;
                *sucessor = removed->right; // o sucessor n tem filho esquerdo pois é nó mais a esquerda;
            }

            node_destroy(removed, bt->key_destroy_fn, bt->val_destroy_fn);
            bt->size--;
            return;

        }else if(cmp<0){
            current = &(*current)->left;
        }else {
            current = &(*current)->right;
        }
        
    }
}
void binary_tree_print(BinaryTree *bt) {
    if (bt == NULL || bt->root == NULL) {
        printf("Árvore vazia.\n");
        return;
    }

    void print_tree_recursive(Node *node) {
        if (node == NULL) {
            printf("NULL");
            return;
        }

        printf("(%d, ", *(int *)node->pair->key); // para ser generica teria q passar como parametro a função de print;

        print_tree_recursive(node->left);

        printf(", ");

        print_tree_recursive(node->right);

        printf(")");
    }

    print_tree_recursive(bt->root);
    printf("\n"); 
}

KeyValPair *binary_tree_min(BinaryTree *bt){
    if (bt == NULL || bt->root == NULL){
        return NULL;
    }

    Node *current = bt->root;

    while (current->left != NULL){
        current = current->left;
    }

    return current->pair;
}

KeyValPair *binary_tree_max(BinaryTree *bt){
    if (bt == NULL || bt->root == NULL){
        return NULL;
    }

    Node *current = bt->root;

    while (current->right != NULL){
        current = current->right;
    }

    return current->pair;
}

KeyValPair *binary_tree_pop_min(BinaryTree *bt){
    if (bt == NULL || bt->root == NULL){
        return NULL;
    }

    Node **current = &bt->root;

    while ((*current)->left != NULL){
        current = &(*current)->left;
    }

    Node *min_node = *current;
    KeyValPair *min_pair = min_node->pair;

    //verifica se o nó minimo tem filho direito (pq n pode ter esquerdo);
    if (min_node->right == NULL){  //se n tiver filhos;
        *current = NULL;
    }else{
        *current = min_node->right;
    }

    free(min_node); //não da node destroy pq n pode destruir o pair key;
    bt->size--;
    return min_pair;
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt){
    if (bt == NULL || bt->root == NULL){
        return NULL;
    }

    Node **current = &bt->root;

    while ((*current)->right != NULL){
        current = &(*current)->right;
    }

    Node *max_node = *current;
    KeyValPair *max_pair = max_node->pair;

    //verifica se o nó maximo tem filho esquerdo (pq n pode ter direito);
    if (max_node->left == NULL){  //se n tiver filhos;
        *current = NULL;
    }else{
        *current = max_node->left;
    }

    free(max_node); //não da node destroy pq n pode destruir o pair key;
    bt->size--;
    return max_pair;
}

Vector *binary_tree_interval(BinaryTree *bt, void *min_key, void *max_key){
    if(bt==NULL || min_key == NULL || max_key == NULL){
        return NULL;
    }

    Vector *intervalo = vector_construct();

    void collect_interval(Node *node){
        if (node == NULL){
            return;
        }

        collect_interval(node->left);

        int cmp_min = bt->cmp_fn(node->pair->key, min_key);
        int cmp_max = bt->cmp_fn(node->pair->key, max_key);
        
        if(cmp_min >= 0 && cmp_max <=0){
            vector_push_back(intervalo, node->pair);
        }
        
        collect_interval(node->right);
    }

    collect_interval(bt->root);

    return intervalo;

}