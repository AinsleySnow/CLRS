#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

typedef struct que_node
{
    int content;
    struct que_node* next;
    struct que_node* prev;
} que_node;

typedef struct queue
{
    que_node* head;
    que_node* tail;
} queue;

int dequeue(queue* q);
void enqueue(queue* q, int content);
void free_queue(queue* q);
bool is_empty(queue* q);

#endif // _QUEUE_H_