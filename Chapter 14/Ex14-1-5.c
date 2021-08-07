#include "./ost/OrderStatisticTree.h"
#include <stdio.h>
#include <stdlib.h>

os_node* os_search(os_node* head, int key)
{
    if (head)
    {
        if (head->key == key)
            return head;
        else if (head->key > key)
            return os_search(head->left, key);
        else
            return os_search(head->right, key);
    }
    else
        return NULL;
}

int main(void)
{
    os_node* root = malloc(sizeof(os_node));
    root->isRed = false;
    root->key = 0;
    root->left = NULL;
    root->prev = NULL;
    root->right = NULL;
    root->size = 1;

    int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    ost_build(&root, data, 10);
    
    os_node* x = os_search(root, 3);
    int j = os_rank(x);
    os_node* y = os_select(root, j + 3);
    printf("%d", y->key);

    ost_delete(&root);
    return 0;
}