/* 
*   implement of treap
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct treap_node
{
    struct treap_node* left;
    struct treap_node* right;
    struct treap_node* prev;
    int priority;
    int key;
} treap_node;

void treap_left_rotate(treap_node* x, treap_node** root)
{
    treap_node* y = x->right;
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
}

void treap_right_rotate(treap_node* y, treap_node** root)
{
    treap_node* x = y->left;
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
}

void treap_insert(treap_node** root, int key, int priority)
{    
    treap_node* trailing = NULL;
    treap_node* current = *root;
    
    do
    {
        trailing = current;

        if(current->key > key)
            current = current->left;
        else
            current = current->right;
    } while (current);
    
    current = malloc(sizeof(treap_node));
    current->key = key;
    current->left = NULL;
    current->right = NULL;
    current->prev = trailing;
    current->priority = priority;
    
    if(key < trailing->key)
        trailing->left = current;
    else
        trailing->right = current;

    while (current->prev)
    {
        if (current->prev->priority < current->priority)
            break;
        
        if (current == current->prev->left)
            treap_right_rotate(current->prev, root);
        else
            treap_left_rotate(current->prev, root);
    }
}

void treap_preorder_walk(treap_node* head, int level)
{
    if (head)
    {
        printf("Level %d: %d, priority = %d\n", level, head->key, head->priority);
        treap_preorder_walk(head->left, level + 1);
        treap_preorder_walk(head->right, level + 1);
    }
}

void build_treap(treap_node** root, int* data, int size, int* priorities, int pri_size)
{
    if (pri_size < size)
        return;

    for (int i = 0; i < size; ++i)
        treap_insert(root, data[i], priorities[i]);
}

void delete_treap(treap_node** root)
{
    if (*root)
    {
        delete_treap(&((*root)->left));
        delete_treap(&((*root)->right));
        free(*root);
        *root = NULL;
    }
}

int main(void)
{
    srand(time(NULL));
    int priorities[20] = { 0 };
    for (int i = 0; i < 20; ++i)
        priorities[i] = rand() % 100000000 + 1;

    int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    treap_node* root = malloc(sizeof(treap_node));
    root->key = 0;
    root->left = NULL;
    root->prev = NULL;
    root->right = NULL;
    root->priority = priorities[0];

    build_treap(&root, data, 10, priorities + 1, 20);
    treap_preorder_walk(root, 0);      
    delete_treap(&root);  

    return 0;    
}