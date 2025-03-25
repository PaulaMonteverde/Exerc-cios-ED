#include <stdio.h>
#include <stdlib.h>
#include "deque.h"
#include "node.h"

typedef struct Deque
{
    Node *head;
    Node *last;
    // int size;
} Deque;

Deque *deque_construct()
{
    Deque *dq = (Deque *)calloc(1, sizeof(Deque));
    dq->head = NULL;
    dq->last = NULL;
    return dq;
}
void deque_push_back(Deque *f, int item)
{
    Node *novo_no = node_construct(item, f->last, NULL);
    if (f->head == NULL)
    {
        f->head = novo_no;
        f->last = novo_no;
    }
    else
    {
        f->last->next = novo_no;
        f->last = novo_no;
    }

    // f->size++;
}
void deque_push_front(Deque *f, int item)
{
    Node *novo_no = node_construct(item, NULL, f->head);
    if (f->head == NULL)
    {
        f->head = novo_no;
        f->last = novo_no;
    }
    else
    {
        f->head->prev = novo_no;
        f->head = novo_no;
    }
    // f->size++;
}
int deque_pop_back(Deque *f)
{
    Node *aux = f->last;
    int valor = aux->value;
    if (f->last != NULL)
    {
        if (f->head == f->last)
        {
            f->head = NULL;
            f->last = NULL;
        }
        else
        {
            f->last = aux->prev;
            f->last->next = NULL;
        }
        node_destroy(aux);
    }
        return valor;
}
int deque_pop_front(Deque *f)
{
    Node *aux = f->head;
    int valor = aux->value;
    if (f->head != NULL)
    {
        if (f->head == f->last)
        {
            f->head = NULL;
            f->last = NULL;
        }
        else
        {
            f->head = aux->next;
            f->head->prev = NULL;
        }
        node_destroy(aux);
    }
        return valor;
}
void deque_destroy(Deque *f)
{
    Node *atual = f->head;
    while (atual != NULL)
    {
        Node *aux = atual;
        atual = atual->next;
        node_destroy(aux);
    }
    free(f);
}
