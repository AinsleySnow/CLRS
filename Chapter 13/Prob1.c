/* 
 * Solution to Problem 13-1, section b.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct persistent_node
{
    struct persistent_node* left;
    struct persistent_node* right;
    int key;
} persistent_node;

void copy(persistent_node* from, persistent_node* to)
{
    to->key = from->key;
    to->left = from->left;
    to->right = from->right;
}

persistent_node* persistent_tree_insert(persistent_node* root, int key)
{
    persistent_node* current = root;
    persistent_node* new_root = malloc(sizeof(persistent_node));
    persistent_node* new_left = NULL;
    persistent_node* new_right = NULL;
    persistent_node* new_trailing = new_root;

    copy(root, new_root);

    do
    {
        if (current->key > key)
        {
            current = current->left;
            new_left = malloc(sizeof(persistent_node));
            if (current)
            {
                copy(current, new_left);
                new_trailing->left = new_left;
                new_trailing = new_left;
            }     
        }  
        else
        {
            current = current->right;
            new_right = malloc(sizeof(persistent_node));
            if (current)
            {
                copy(current, new_right);
                new_trailing->right = new_right;
                new_trailing = new_right;
            }
        }    
    } while (current);
    
    current = malloc(sizeof(persistent_node));
    current->key = key;
    current->left = NULL;
    current->right = NULL;

    if (new_trailing->key > current->key)
        new_trailing->left = current;
    else
        new_trailing->right = current;
    
    return new_root;
}

void initial_persistent_tree_build(persistent_node* root, int* data, int size)
{
    persistent_node* current = NULL;
    persistent_node* trailing = NULL;
    for (int i = 0; i < size; ++i)
    {
        current = root;
        trailing = NULL;

        do
        {
            trailing = current;

            if (current->key > data[i])
                current = current->left;
            else
                current = current->right;
        } while (current);
        
        current = malloc(sizeof(persistent_node));
        current->key = data[i];
        current->left = NULL;
        current->right = NULL;
        if (trailing->key > current->key)
            trailing->left = current;
        else
            trailing->right = current;
    }
}

void persistent_inorder_walk(persistent_node* head, int height)
{
    if (head)
    {
        persistent_inorder_walk(head->left, height + 1);
        printf("In height %d: %d", height, head->key);
        persistent_inorder_walk(head->right, height + 1);
    }
}

void delete_single_persistent_tree(persistent_node** head)
{
    if ((*head)->left)
        delete_single_persistent_tree(&((*head)->left));
    if ((*head)->right)
        delete_single_persistent_tree(&((*head)->right));
    free(*head);
    *head = NULL;
}

int main(void)
{
    persistent_node* root = malloc(sizeof(persistent_node));
    root->key = 8;
    root->left = NULL;
    root->right = NULL;

    int data[10] = { 4, 12, 2, 6, 10, 14, 1, 3, 5, 7 };
    initial_persistent_tree_build(root, data, 10);
    persistent_inorder_walk(root, 0);

    persistent_node* insert1 = persistent_tree_insert(root, -1);
    persistent_inorder_walk(insert1, 0);

    persistent_node* insert2 = persistent_tree_insert(insert1, 9);
    persistent_inorder_walk(insert2, 0);

    persistent_node* insert3 = persistent_tree_insert(insert2, 15);
    persistent_inorder_walk(insert3, 0);

    delete_single_persistent_tree(&root);
    delete_single_persistent_tree(&insert1);
    delete_single_persistent_tree(&insert2);
    delete_single_persistent_tree(&insert3);

    return 0;
}