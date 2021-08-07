#include "DoublyLinkedList.h"
#include <stdlib.h>

void doubly_insert(doubly_link_node* head, int value)
{
    doubly_link_node* current = head;
    while(current->next)
        current = current->next;
    
    current->next = malloc(sizeof(doubly_link_node));
    current->next->next = NULL;
    current->next->prev = current;
    current->next->value = value;
}

void doubly_delete(doubly_link_node* head, int key)
{
    doubly_link_node* current = head;
    while(current)
    {
        if(current->value == key)
        {
            current->prev = current->next;
            free(current);
            current = NULL;
            return;
        }
        current = current->next;
    }
}

doubly_link_node* doubly_search(doubly_link_node* head, int key)
{
    doubly_link_node* current = head;
    while(current)
    {
        if(current->value == key)
            return current;
        current = current->next;
    }
    return NULL;
}

void doubly_list_delete(doubly_link_node** head)
{
    doubly_link_node* next = NULL;
    doubly_link_node* current = *head;
    
    do
    {
        next = current->next;
        free(current);
        current = next;
    }while(next);
    *head = NULL;
}