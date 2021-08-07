#include "Stack/stack.h"
#include "../Chapter 12/bst/BinarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 256

void walk_a_binary_tree(node* root)
{
    Stack s = {NULL, 0, 0};
    CreateAStack(&s, STACK_SIZE);
    
    node* current = root;
    do
    {
        while(current)
        {
            if(current->right)
                Push(s, (long)(current->right));
            printf("%d ", current->key);
            current = current->left;
        }
        current = Pop(&s);
    } while (!IsStackEmpty(s));
}

int main(void)
{
    int nums[10] = {376, 4, 98347, 35, 48, 98, 234, -374, 4890, -37638};
    node root = {0, NULL, NULL, NULL};
    tree_build(&root, nums, 10);

    walk_a_binary_tree(&root);
    delete_the_tree(&(&root));
    return 0;
}