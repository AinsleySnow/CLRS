#include "ost/OrderStatisticTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void os_insert_fixup(os_node* z, os_node** root);

void my_os_insert(os_node** root, int value, int* ans)
{
    os_node* current = *root;
    os_node* trailing = NULL;

    do
    {
        trailing = current;
        current->size += 1;

        if (current->key > value)
        {
            current = current->left;
            (*ans) += current->right ? current->right->size + 1 : 1;
        }     
        else
            current = current->right;
    } while (current);

    current = malloc(sizeof(os_node));
    current->isRed = true;
    current->key = value;
    current->left = NULL;
    current->prev = trailing;
    current->right = NULL;
    current->size = 1;

    if (trailing->key > value)
        trailing->left = current;
    else
        trailing->right = current;

    os_insert_fixup(current, root);
    (*root)->isRed = false;
}

int main(void)
{
    int data[5] = { 5, 4, 3, 2, 1 };

    os_node* root = malloc(sizeof(os_node));
    root->isRed = false;
    root->key = 5;
    root->left = NULL;
    root->prev = NULL;
    root->right = NULL;
    root->size = 1;

    int ans = 0;
    for (int i = 1; i < 5; ++i)
        my_os_insert(&root, data[i], &ans);
    printf("%d", ans);

    ost_delete(&root);
    root = NULL;
    return 0;
}