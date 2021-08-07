#include <stdio.h>
#include <stdlib.h>
#include "IntervalTree.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

bool is_overlap(interval a, interval b)
{
    return b.high >= a.low || a.high >= b.low;
}

void int_left_rotate(int_node* x, int_node** root)
{
    int_node* y = x->right;
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

    x->max = max(x->left ? x->left->i.high : ~0x7fffffff,
                 x->right ? x->right->i.high : ~0x7fffffff);
    y->max = max(y->left ? y->left->i.high : ~0x7fffffff,
                 y->right ? y->right->i.high : ~0x7fffffff);
}

void int_right_rotate(int_node* y, int_node** root)
{
    int_node* x = y->left;
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
    
    y->left = x;
    x->prev = y;

    x->max = max(x->left ? x->left->i.high : ~0x7fffffff,
                 x->right ? x->right->i.high : ~0x7fffffff);
    y->max = max(y->left ? y->left->i.high : ~0x7fffffff,
                 y->right ? y->right->i.high : ~0x7fffffff);
}

void int_insert_fixup(int_node* z, int_node** root)
{
    while (z->prev && z->prev->isRed)
    {
        if (z->prev == z->prev->prev->left)
        {
            int_node* y = z->prev->prev->right;

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
                int_left_rotate(z, root);
            }
            else
            {
                z->prev->isRed = false;
                if (z->prev->prev)
                {
                    z->prev->prev->isRed = true;
                    int_right_rotate(z->prev->prev, root);
                }
            }
        }
        else
        {
            int_node* y = z->prev->prev->left;

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
                int_right_rotate(z, root);
            }
            else
            {
                z->prev->isRed = false;
                if (z->prev->prev)
                {
                    z->prev->prev->isRed = true;
                    int_left_rotate(z->prev->prev, root);
                }
            }
        }
    }
}

void int_insert(int_node** root, interval i)
{
    int_node* trailing = NULL;
    int_node* current = *root;

    while(current)
    {
        trailing = current;
        if (i.low < current->i.low)
            current = current->left;
        else
            current = current->right;
    }

    int_node* temp = NULL;
    if (i.low < trailing->i.low)
    {
        trailing->left = malloc(sizeof(int_node));
        temp = trailing->left;
    }
    else
    {
        trailing->right = malloc(sizeof(int_node));
        temp = trailing->right;
    }

    temp->i = i;
    temp->left = NULL;
    temp->prev = trailing;
    temp->right = NULL;
    temp->isRed = true;
    temp->max = ~0x7fffffff;

    int_insert_fixup(temp, root);
    (*root)->isRed = false;
}

void int_delete(int_node** head)
{
    if (*head != NULL)
    {
        int_delete(&((*head)->left));
        int_delete(&((*head)->right));
        free(*head);
        *head = NULL;
    }
}

void int_build(int_node** root, interval* data, int size)
{
    for (int i = 0; i < size; ++i)
        int_insert(root, data[i]);
}

int_node* interval_search(int_node* root, interval i)
{
    int_node* current = root;

    while (current && !is_overlap(current->i, i))
    {
        if (current->left && current->left->max >= i.low)
            current = current.left;
        else
            current = current->right;
    }

    return current;
}