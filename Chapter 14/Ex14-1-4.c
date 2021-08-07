#include "ost/OrderStatisticTree.h"
#include <stdio.h>
#include <stdlib.h>

int os_key_rank(os_node* head, int k)
{
    int ans = 0;

    if (k < head->key)
    {
        ans += os_key_rank(head->left, k);
        ans += head->right->size;
    }  
    else if (k > head->key)
    {
        ans += os_key_rank(head->right, k);
        ans += head->left->size;
    }
    else
        ans += 1;
    
    return ans;
}

int main(void)
{
    os_node* root = malloc(sizeof(os_node));
    root->isRed = false;
    root->key = 1;
    root->left = NULL;
    root->prev = NULL;
    root->right = NULL;
    root->size = 1;

    int data[10] = { 489, 3487, 49, 6, 29, 20, 4, 890, 32948, 7 };
    ost_build(&root, data, 10);
    printf("%d", os_key_rank(root, 3487));

    ost_delete(&root);
    return 0;
}