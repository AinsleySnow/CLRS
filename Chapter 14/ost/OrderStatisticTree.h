#ifndef _ORDER_STATISTIC_TREE_H_
#define _ORDER_STATISTIC_TREE_H_

#include <stdbool.h>

typedef struct os_node
{
    struct os_node* left;
    struct os_node* right;
    struct os_node* prev;
    int key;
    int size;
    bool isRed;
} os_node;

void os_insert(os_node** root, int value);
void ost_delete(os_node** head);
void ost_build(os_node** root, int* data, int size);
os_node* os_select(os_node* head, int i);
int os_rank(os_node* x);

#endif // _ORDER_STATISTIC_TREE_H_