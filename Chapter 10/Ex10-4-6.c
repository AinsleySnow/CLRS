#include <stdio.h>
#include <stdlib.h>

typedef struct lcrs_node
{
    lcrs_node* left_child;
    lcrs_node* right_sibling;
    lcrs_node* parent;
    int key;
}lcrs_node;

void walk_a_lcrs_tree(lcrs_node* root)
{
    if(root)
    {
        walk_a_lcrs_tree(root->left_child);
        walk_a_lcrs_tree(root->right_sibling);
        printf("%d ", root->key);
    }
}

void lcrs_tree_insert(lcrs_node* root, int size, int* keys)
{
    root->left_child = malloc(sizeof(lcrs_node) * size);
    
    for(int i = 0; i < size; ++i)
    {
        (root->left_child + i)->key = keys[i];
        (root->left_child + i)->left_child = NULL; 
        (root->left_child + i)->parent = root;
    }

    for(int i = 0; i < size - 1; ++i)
        (root->left_child + i)->right_sibling = root->left_child + i + 1;
    (root->left_child + size - 1)->right_sibling = NULL;
}

void lcrs_tree_delete(lcrs_node** root)
{
    if(*root)
    {
        lcrs_node* current = *root;
        while(current->right_sibling)
        {
            if(current->right_sibling->left_child)
                lcrs_tree_delete(&current->right_sibling->left_child);
            current = current->right_sibling;
        }
        free((*root)->left_child);
        (*root)->left_child = NULL;
        (*root)->right_sibling = NULL;
    }
}

int main(void)
{
    lcrs_node* root = {NULL, NULL, NULL, 46};
    lcrs_node* current = NULL;
    
    lcrs_tree_insert(root, 5, {3, 4, 5, 79, 56});
    current = root->left_child[3];

    lcrs_tree_insert(current, 6, {-9, 34895638, 68, 2, -2, 4398});
    current += 1;
    lcrs_tree_insert(current, 3, {-2, 500, -8});
    current = current->left_child;
    lcrs_tree_insert(current, 2, {0, -89});

    walk_a_lcrs_tree(root);
    lcrs_tree_delete(&root);
    
    return 0;
}