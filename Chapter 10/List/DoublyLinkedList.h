#ifndef _DOUBLY_LINKED_LIST_H_
#define _DOUBLY_LINKED_LIST_H_

typedef struct doubly_link_node
{
    struct doubly_link_node* next;
    struct doubly_link_node* prev;
    int value;
}doubly_link_node;

void doubly_insert(doubly_link_node* head, int value);
void doubly_delete(doubly_link_node* head, int key);
doubly_link_node* doubly_search(doubly_link_node* head, int key);
void doubly_list_delete(doubly_link_node** head);

#endif // _DOUBLY_LINKED_LIST_H_