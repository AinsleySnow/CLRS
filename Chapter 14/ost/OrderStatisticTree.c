#include "OrderStatisticTree.h"
#include <stdlib.h>
#include <stdio.h>

void os_left_rotate(os_node* x, os_node** root)
{
    os_node* y = x->right;
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

    x->size = x->right ? x->right->size : 0 + 
                x->left ? x->left->size : 0 + 1;
    y->size = y->right ? y->right->size : 0 +
                y->left ? y->left->size : 0 + 1;
}

void os_right_rotate(os_node* y, os_node** root)
{
    os_node* x = y->left;
    y->left = x->right;

    if (x->right)
        x->right->prev = y;

    x->prev = y->prev;
    if (y->prev)
    {
        if (y == y->prev->right)
            y->prev->right = x;
        else
            y->prev->left = x;
    }
    else
        *root = x;

    x->right = y;
    y->prev = x;

    x->size = x->right ? x->right->size : 0 + 
                x->left ? x->left->size : 0 + 1;
    y->size = y->right ? y->right->size : 0 +
                y->left ? y->left->size : 0 + 1;
}

void os_insert_fixup(os_node* z, os_node** root)
{
    while (z->prev && z->prev->isRed)
    {
        if (z->prev == z->prev->prev->left)
        {
            os_node* y = z->prev->prev->right;

            if (y && y->isRed)
            {
                z->prev->isRed = false;
                y->isRed = false;
                z->prev->prev->isRed = true;
                z = z->prev->prev;
            }
            else if (z == z->prev->right)
            {
                z = z->prev;
                os_left_rotate(z, root);
            }
            else
            {
                z->prev->isRed = false;
                if (z->prev->prev)
                {
                    z->prev->prev->isRed = true;
                    os_right_rotate(z->prev->prev, root);
                }
            }
        }
        else
        {
            os_node* y = z->prev->prev->left;

            if (y && y->isRed)
            {
                z->prev->isRed = false;
                y->isRed = false;
                z->prev->prev->isRed = true;
                z = z->prev->prev;
            }
            else if (z == z->prev->left)
            {
                z = z->prev;
                os_right_rotate(z, root);
            }
            else
            {
                z->prev->isRed = false;
                if (z->prev->prev)
                {
                    z->prev->prev->isRed = true;
                    os_left_rotate(z->prev->prev, root);
                }
            }
        }
    }
}

void os_insert(os_node** root, int value)
{
    os_node* trailing = NULL;
    os_node* current = *root;

    while(current)
    {
        ++(current->size);
        trailing = current;
        if(value < current->key)
            current = current->left;
        else
            current = current->right;
    }

    os_node* temp = NULL;
    if(value < trailing->key)
    {
        trailing->left = malloc(sizeof(os_node));
        temp = trailing->left;
    }
    else
    {
        trailing->right = malloc(sizeof(os_node));
        temp = trailing->right;
    }

    temp->isRed = true;
    temp->left = NULL;
    temp->prev = trailing;
    temp->right = NULL;
    temp->key = value;
    temp->size = 1;

    os_insert_fixup(temp, root);
    (*root)->isRed = false;
}

void ost_delete(os_node** head)
{
    if(*head != NULL)
    {
        ost_delete(&((*head)->left));
        ost_delete(&((*head)->right));
        free(*head);
        *head = NULL;
    }
}

void ost_build(os_node** root, int* data, int size)
{
    for(int i = 0; i < size; ++i)
        os_insert(root, data[i]);
}

os_node* os_select(os_node* head, int i)
{
    if (head)
    {
        int r = head->left->size + 1;
        if (i == r)
            return head;
        else if (i < r)
            return os_select(head->left, i);
        else
            return os_select(head->right, i - r);
    }
    else
        return NULL;
}

int os_rank(os_node* x)
{
    int r = x->left->size + 1;
    os_node* y = x;
    while (y->prev)
    {
        if (y == y->prev->right)
            r += y->prev->left->size + 1;
        y = y->prev;
    }
    return r;
}