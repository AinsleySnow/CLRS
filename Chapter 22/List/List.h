#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>

typedef struct list_node
{
    void* content;
    struct list_node* next;
    struct list_node* prev;
} list_node;

typedef struct list
{
    list_node* head;
    list_node* tail;
} list;

void list_create(list* l, void* content);
void list_append(list* l, void* content);
void list_remove(list* l, void* content);
void list_free(list* l);
bool is_in(list* l, void* content);

#endif // _LIST_H_