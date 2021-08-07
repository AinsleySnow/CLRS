/*
*   Solution to Problem 13-3, section b and c.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#undef max

typedef struct avl_node
{
    struct avl_node* prev;
    struct avl_node* left;
    struct avl_node* right;
    int height;
    int key;
} avl_node;

int max(int a, int b)
{
    return a > b ? a : b;
}

void refresh_height(avl_node* x)
{
    x->height = max(x->left ? x->left->height : 0, 
                x->right ? x->right->height : 0);
    if (x->left || x->right)
        x->height += 1;
}

void avl_left_rotate(avl_node* x, avl_node** root)
{
    avl_node* y = x->right;
    x->right = y->left;

    if (y->left)
        y->left->prev = x;
    
    y->prev = x->prev;
    if (x->prev)
    {
        if (x == x->prev->left)
            x->prev->left = y;
        else
            x->prev->right = y;
    }
    else
        *root = y;

    y->left = x;
    x->prev = y;

    refresh_height(x);
    refresh_height(y);
}

void avl_right_rotate(avl_node* y, avl_node** root)
{
    avl_node* x = y->left;
    y->left = x->right;

    if (x->right)
        x->right->prev = y;
    
    x->prev = y->prev;
    if (y->prev)
    {
        if (y == y->prev->left)
            y->prev->left = x;
        else
            y->prev->right = x;
    }
    else
        *root = x;

    x->right = y;
    y->prev = x;

    refresh_height(x);
    refresh_height(y);
}

bool avl_check_balance(avl_node* x)
{
    int difference = (x->left ? x->left->height : 0) - 
                     (x->right ? x->right->height : 0);
    return (difference == 0 || difference == -1 || difference == 1);
}

void avl_balance(avl_node* unbalance, avl_node** root, int path)
{
    int offset = 0, mask = 0b11;
    while ((mask << offset) & path)
        offset += 2;
    path >>= offset - 4;

    switch (path)
    {
        case 0b1111: // case '\':
        avl_left_rotate(unbalance, root);
        break;

        case 0b1010: // case '/':
        avl_right_rotate(unbalance, root);
        break;

        case 0b1110: // case '<':
        avl_left_rotate(unbalance->left, root);
        avl_right_rotate(unbalance, root);
        break;

        case 0b1011: // case '>':
        avl_right_rotate(unbalance->right, root);
        avl_left_rotate(unbalance, root);
        break;
    }
}

void avl_insert(avl_node** root, int key)
{
    avl_node* trailing = NULL;
    avl_node* current = *root;

    do
    {
        trailing = current;
        
        if (current->key > key)
            current = current->left;
        else
            current = current->right;
    } while(current);
    
    current = malloc(sizeof(avl_node));
    current->height = 0;
    current->key = key;
    current->left = NULL;
    current->right = NULL;
    current->prev = trailing;

    if (trailing->key > key)
        trailing->left = current;
    else
        trailing->right = current;

    int path = 0; // '\' 0b11 (3), '/' 0b10 (2).
    int current_bit = 0;

    while (current->prev)
    {
        trailing = current;
        current = current->prev;
        if (trailing == current->right)
            path |= 0b11 << current_bit;
        else
            path |= 0b10 << current_bit;
        current_bit += 2;

        refresh_height(current);
        if (!avl_check_balance(current))
        {
            avl_balance(current, root, path);
            break;
        }
    }   
}

void delete_avl_tree(avl_node** root)
{
    if (*root)
    {
        delete_avl_tree(&((*root)->left));
        delete_avl_tree(&((*root)->right));
        free(*root);
        *root = NULL;
    }
}

void build_avl_tree(avl_node** root, int* data, int size)
{
    for (int i = 0; i < size; ++i)
        avl_insert(root, data[i]);
}

void avl_preorder_walk(avl_node* head, int level)
{
    if (head)
    {
        printf("Level %d: %d, height = %d\n", level, head->key, head->height);
        avl_preorder_walk(head->left, level + 1);
        avl_preorder_walk(head->right, level + 1);
    }
}

int main(void)
{
    avl_node* root1 = malloc(sizeof(avl_node));
    root1->height = 0;
    root1->key = 0;
    root1->left = NULL;
    root1->right = NULL;
    root1->prev = NULL;

    int data1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    build_avl_tree(&root1, data1, 10);
    avl_preorder_walk(root1, 0);
    delete_avl_tree(&root1);

    return 0;
}