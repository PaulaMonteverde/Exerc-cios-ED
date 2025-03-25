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
        if (key_destroy_fn != NULL)
            key_destroy_fn(node->pair->key);
        if (val_destroy_fn != NULL)
            val_destroy_fn(node->pair->value);
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
    if (bt == NULL || key == NULL) return NULL;

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
    if (bt == NULL) return;

    void destroy_nodes(Node *node) {
        if (node == NULL) return;

        destroy_nodes(node->left);
        destroy_nodes(node->right);

        node_destroy(node, bt->key_destroy_fn, bt->val_destroy_fn);
    }

    destroy_nodes(bt->root);

    free(bt);
}
