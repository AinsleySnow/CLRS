#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#include <stdbool.h>

typedef struct rbt_node
{
    struct rbt_node *right;
    struct rbt_node *left;
    struct rbt_node *prev;
    bool isRed;
    int value;
} rbt_node;

extern rbt_node nil;

void rb_insert(rbt_node** root, int value);
void rbt_build(rbt_node** root, int* data, int size);
void rbt_delete(rbt_node** head);

#endif // _RED_BLACK_TREE_H_