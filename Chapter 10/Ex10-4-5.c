#include "Stack/stack.h"
#include "../Chapter 12/bst/BinarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 256

void walk_a_binary_tree(node* root)
{
    stack s = { NULL, 0, 0 };
    create_stack(&s, STACK_SIZE);
    
    node* current = root;
    while (current)
    {
        push(&s, (unsigned long long)current);
        current = current->left;
    }

    while (!is_stack_empty(&s))
    {
        current = (node*)pop(&s);
        printf("%d ", current->key);
        current = current->right;
        while (current)
        {
            push(&s, (unsigned long long)current);
            current = current->left;
        }
    }
}

int main(void)
{
    int nums[10] = { 376, 4, 98347, 35, 48, 98, 234, -374, 4890, -37638 };
    node* root = calloc(1, sizeof(node));
    tree_build(root, nums, 10);

    inorder_tree_walk(root);
    printf("\n");
    walk_a_binary_tree(root);
    delete_the_tree(&root);
    return 0;
}