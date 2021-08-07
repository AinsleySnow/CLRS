#ifndef _INTERVAL_TREE_H_
#define _INTERVAL_TREE_H_

#include <stdbool.h>
#undef max

typedef struct interval
{
    int low;
    int high;
} interval;

typedef struct int_node
{
    struct int_node* left;
    struct int_node* right;
    struct int_node* prev;
    interval i;
    int max;
    bool isRed;
} int_node;

void int_insert(int_node** root, interval i);
void int_delete(int_node** head);
void int_build(int_node** root, interval* data, int size);
int_node* interval_search(int_node* root, interval i);

#endif // _INTERVAL_TREE_H_