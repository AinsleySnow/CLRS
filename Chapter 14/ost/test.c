#include "OrderStatisticTree.h"
#include <stdio.h>
#include <stdlib.h>

void os_inorder_walk(os_node* head, int level)
{
    if (head)
    {
        os_inorder_walk(head->left, level + 1);
        printf("size = %3d, color = %5s, level = %3d, key = %3d\n", 
                head->size, 
                head->isRed ? "Red" : "Black", 
                level, 
                head->key);
        os_inorder_walk(head->right, level + 1);
    }
}

int main(void)
{
    int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    os_node* root = malloc(sizeof(os_node));
    root->isRed = false;
    root->key = 456;
    root->left = NULL;
    root->prev = NULL;
    root->right = NULL;
    root->size = 1;

    ost_build(&root, data, 10);
    os_inorder_walk(root, 0);

    os_insert(&root, 99);
    printf("Rank of %d: %d\n", root->key, os_rank(root));
    
    os_node* result = os_select(root, 4);
    printf("%dth node in order-statistic-tree: %d\n", 4, result->key);

    result = os_select(root, 100);
    if (result)
        printf("Crashed...\n");
    else
        printf("Normal situation.\n");
    
    os_inorder_walk(root, 0);

    ost_delete(&root);
    return 0;
}