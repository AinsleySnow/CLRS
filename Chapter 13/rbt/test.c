#include "RedBlackTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int level = 0;

void preorder_walk(rbt_node* x)
{
    if(x != &nil)
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
    root->left = &nil;
    root->prev = &nil;
    root->right = &nil;
    root->value = 123;

    srand(time(NULL));
    int num[10];
    for (int i = 0; i < 10; ++i)
    {
        num[i] = rand() % 100;
        printf("num[%d] = %d\n", i, num[i]);
    }

    rbt_build(&root, num, 10);
    printf("Tree before deleting num[0] and num[2]:\n");
    preorder_walk(root);

    rb_delete(&root, rb_search(root, num[0]));
    rb_delete(&root, rb_search(root, num[2]));
    printf("Tree after deleting num[0] and num[2]:\n");
    preorder_walk(root);

    rbt_delete(&root);
    return 0;
}