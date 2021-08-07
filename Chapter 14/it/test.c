#include <stdlib.h>
#include <stdio.h>
#include "IntervalTree.h"

void int_inorder_walk(int_node* head, int level)
{
    if (head)
    {
        int_inorder_walk(head->left, level + 1);
        printf("low = %2d, high = %2d, color = %5s, level = %2d\n", 
                head->i.low,
                head->i.high, 
                head->isRed ? "Red" : "Black", 
                level);
        int_inorder_walk(head->right, level + 1);
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
    root->max = ~0x7fffffff;
    
    int_build(&root, data + 1, 9);
    int_inorder_walk(root, 0);

    int_insert(&root, {5, 8});
    int_insert(&root, {-100, 100});
    int_inorder_walk(root, 0);

    int_node* ans = interval_search(root, {2,6});
    printf("%d %d\n", ans->i.low, ans->i.high);
    
    int_delete(&root);
    return 0;
}