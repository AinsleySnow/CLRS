#include "Queue.h"
#include <stdlib.h>

void* dequeue(queue* q)
{
    if (q->head)
    {
        que_node* n = q->head;
        q->head = n->next;
        if (q->head == NULL)
            q->tail = NULL;
        void* content = n->content;
        free(n);
        return content;
    }

    return NULL;
}

void enqueue(queue* q, void* content)
{
    que_node* n = calloc(1, sizeof(que_node));
    n->content = content;

    if (q->head)
    {
        n->prev = q->tail;
        q->tail->next = n;
        q->tail = n;
    }
    else
    {
        q->head = n;
        q->tail = n;
    }
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
    return (q->head == NULL);
}