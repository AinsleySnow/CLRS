#ifndef _SINGLY_LINKED_LIST_H_
#define _SINGLY_LINKED_LIST_H_

typedef struct singly_link_node
{
	struct singly_link_node* next;
	int value;
} singly_link_node;

void singly_insert(singly_link_node* head, int key);
void singly_delete(singly_link_node* head, int key);
singly_link_node* singly_search(singly_link_node* head, int key);
void singly_list_delete(singly_link_node** head);

#endif // _SINGLY_LINKED_LIST_H_