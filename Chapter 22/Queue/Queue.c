#include "Queue.h"
#include <stdlib.h>

void* dequeue(queue* q)
{
    que_node* n = q->head;
    q->head = n->next;
    void* ans = n->content;
    
    free(n);
    return ans;
}

void enqueue(queue* q, const void* content)
{
    que_node* n = calloc(1, sizeof(que_node));
    n->content = content;
    n->prev = q->tail;
    q->tail = n;
    if (!q->head)
        q->head = n;
} 

void free_queue(queue* q)
{
    que_node* current = q->head;
    que_node* next = NULL;
    do
    {
        next = current->next;
        free(current);
        current = next;
    } while (current);

    q->head = NULL;
    q->tail = NULL;
}

bool is_empty(queue* q)
{
    return (bool)q->head;
}