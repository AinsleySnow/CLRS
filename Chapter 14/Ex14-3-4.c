#include <stdlib.h>
#include <stdio.h>
#include "it/IntervalTree.h"

#define Print_Interval(x) printf("%d %d\n", x->i.low, x->i.high)

bool is_overlap(interval a, interval b)
{
    return b.high >= a.low || a.high >= b.low;
}

void list_all_overlapped_interval(int_node* x, interval i)
{
    if (x)
    {
        if (x->left->max >= i.low)
            list_all_overlapped_interval(x->left, i);
        if (is_overlap(x->i, i))
            Print_Interval(x);
        if (x->right->max >= i.low)
            list_all_overlapped_interval(x->right, i);
    }
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

    int_build(&root, data + 1, 9);
    list_all_overlapped_interval(root, {0,10});
    int_delete(&root);
    
    return 0;
}