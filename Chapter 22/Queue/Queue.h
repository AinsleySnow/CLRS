#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

typedef struct que_node
{
    void* content;
    que_node* next;
    que_node* prev;
} que_node;

typedef struct queue
{
    que_node* head;
    que_node* tail;
} queue;

void* dequeue(queue* q);
void enqueue(queue* q, void* content);
void free_queue(queue* q);
bool is_empty(queue* q);

#endif // _QUEUE_H_