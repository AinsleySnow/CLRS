#include "SinglyLinkedList.h"
#include <stdlib.h>

void singly_insert(singly_link_node* head, int key)
{
	singly_link_node* current = head;
	
	while (current->next)
		current = current->next;
	
	current->next = malloc(sizeof(singly_link_node));
	current = current->next;
	current->next = NULL;
	current->value = key;
}

void singly_delete(singly_link_node* head, int key)
{
	singly_link_node* current = head;
	singly_link_node* trailing = NULL;

	while(current)
	{
		if(current->value == key)
		{
			trailing->next = current->next;
			free(current);
			current = NULL;
			return;	
		}
		trailing = current;
		current = current->next;
	}
}

singly_link_node* singly_search(singly_link_node* head, int key)
{
	singly_link_node* current = head;

	while(current)
	{
		if(current->value == key)
			return current;
		current = current->next;
	}

	return NULL;
}

void singly_list_delete(singly_link_node** head)
{
    singly_link_node* next = NULL;
    singly_link_node* current = *head;
    
    do
    {
        next = current->next;
        free(current);
        current = next;
    }while(next);
    *head = NULL;
}