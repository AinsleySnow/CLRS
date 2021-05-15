#include "BinarySearchTree.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int tree_build(node* root, int* data, int size)
{
    int flag = 1;
    for(int i = 0; i < size && flag; ++i)
       flag &= tree_insert(root, data[i]);
    return flag;
}

void delete_the_tree(node** head)
{
    if(*head != NULL)
    {
        delete_the_tree(&((*head)->left));
        delete_the_tree(&((*head)->right));
        free(*head);
        *head = NULL;
    }
}

void inorder_tree_walk(node* x)
{
    if(x != NULL)
    {
        inorder_tree_walk(x->left);
        printf("%d ", x->key);
        inorder_tree_walk(x->right);
    }
}

node* tree_search(node* x, int k)
{
    if(x == NULL || x->key == k)
        return x;
    if(k < x->key)
        return tree_search(x->left);
    else
        return tree_search(x->right);
}

node* iterative_tree_search(node* x, int k)
{
    while(x != NULL && x->key != k)
    {
        if(k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

node* tree_min(node* x)
{
    while(x->left != NULL)
        x = x->left;
    return x;
}

node* tree_max(node* x)
{
    while(x->right != NULL)
        x = x->right;
    return x;
}

node* inorder_tree_successor(node* x)
{
    if(x->right != NULL)
        return tree_min(x->right);
    
    node* y = x->previous;
    while(y != NULL && x == y->right)
    {
        x = y;
        y = y->previous;
    }
    return y;
}

int tree_insert(node* root, int value)
{
    if(!root)
        return 0;
     
    node* trailing = root;
    node* current = root;
    while(current)
    {
        trailing = current;
        
        if(value < current->key)
            current = current->left;
        else
            current = current->right;
    }
    if(value < trailing->key)
    {
        trailing->left = calloc(1,sizeof(node));
        if(!trailing->left)
            return 0;

        trailing->left->key = value;
        trailing->left->left = NULL;
        trailing->left->right = NULL;
        trailing->left->previous = trailing;
    }
    else
    {
        trailing->right = calloc(1,sizeof(node));
        if(!trailing->right)
            return 0;

        trailing->right->key = value;
        trailing->right->left = NULL;
        trailing->right->right = NULL;
        trailing->right->previous = trailing;
    } 
    return 1;  
}

void transplant(node* u, node* v)
{
    if(u == u->previous->left)
        u->previous->left = v;
    else
        u->previous->right = v;
    if(!v)
        v->previous = u->previous;
}

void tree_delete(node* z)
{
    if(z->left == NULL)
        transplant(z, z->right);
    else if(z->right == NULL)
        transplant(z, z->left);
    else
    {
        node* successor = tree_min(z->right);
        if(successor->previous != z)
        {
            transplant(successor, successor->right);
            successor->right = z->right;
            successor->right->previous = successor;
        }
        transplant(z, successor);
        successor->left = z->left;
        successor->left->previous = successor;
    }
    //free(z); //Better do this in its caller.
}