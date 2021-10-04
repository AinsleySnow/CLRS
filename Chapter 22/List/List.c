#include "List.h"
#include <stdlib.h>

void list_create(list* l, void* content)
{
    l->head = calloc(1, sizeof(list_node));
    l->head->content = content;
    l->tail = l->head;
}

void list_append(list* l, void* content)
{
    list_node* new_node = calloc(1, sizeof(list_node));
    new_node->content = content;
    new_node->prev = l->tail;

    l->tail->next = new_node;
    l->tail = new_node;
}

void list_remove(list* l, void* content)
{
    list_node* current = l->head;
    while (current)
    {
        if (current->content == content)
        {
            current->prev = current->next;
            current->next->prev = current->prev;
            free(current);
            return;
        }
    }
}

void list_free(list* l)
{
    list_node* current = l->head;
    list_node* trailing = NULL;
    while (current)
    {
        trailing = current;
        current = current->next;
        free(trailing);
    }

    l->head = NULL;
    l->tail = NULL;
}

bool is_in(list* l, void* content)
{
    list_node* current = l->head;
    while (current)
    {
        if (content == current->content)
            return true;
        current = current->next;
    }
    return false;
}