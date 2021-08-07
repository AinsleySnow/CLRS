#include <stdio.h>
#include <stdlib.h>
#include "it/IntervalTree.h"

int_node* interval_search_exactly(int_node* root, interval i)
{
    int_node* current = root;
    int_node* trailing = NULL;
    
    do
    { 
        if (current->i == i)
            return current;

        trailing = current;
        if (i.low < current->i.low)
            current = current->left;
        else 
            current = current->right;
    } while (current);

    return current;
}

int main(void)
{
    interval data[10] = 
    { 
        {1,2}, {2,6}, {3,8}, {347, 900}, {2,57}, 
        {3,90}, {-2,4}, {6,8}, {90,100}, {1,10} 
    };

    int_node* root = malloc(sizeof(int_node));
    root->i = data[0];
    root->isRed = false;
    root->left = NULL;
    root->right = NULL;
    root->prev = NULL;
    root->max = ~0x7fffffff;

    int_build(&root, data + 1, 9);
    int_node* ans = interval_search_exactly(root, {6,8});
    printf("%d %d", ans->i.low, ans->i.high);

    int_delete(&root);
    return 0;
}