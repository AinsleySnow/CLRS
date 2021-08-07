#include "RedBlackTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int level = 0;

void preorder_walk(rbt_node* x)
{
    if(x)
    {
        ++level;
        printf("%4d, color = %5s, level = %3d\n", x->value, x->isRed ? "red" : "black", level);
        preorder_walk(x->left);
        preorder_walk(x->right);
        --level;
    }
}

int main(void)
{
    rbt_node* root = malloc(sizeof(rbt_node));
    root->isRed = false;
    root->left = NULL;
    root->prev = NULL;
    root->right = NULL;
    root->value = 123;

    int num[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    rbt_build(&root, num, 10);
    preorder_walk(root);
    rbt_delete(&root);
    return 0;
}