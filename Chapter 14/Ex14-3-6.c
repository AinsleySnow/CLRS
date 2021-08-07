#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct gap_node
{
    struct gap_node* left;
    struct gap_node* right;
    struct gap_node* prev;
    int left_gap;
    int right_gap;
    int key;
    bool isRed;
} gap_node;

void refresh_left_gap(gap_node* x)
{
    x->left_gap = abs(x->key - (x->left ? x->left->key : 0));
}

void refresh_right_gap(gap_node* x)
{
    x->right_gap = abs(x->key - (x->right ? x->right->key : 0));
}

void gap_left_rotate(gap_node* x, gap_node** root)
{
    gap_node* y = x->right;
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

    refresh_left_gap(x);
    refresh_right_gap(x);
    refresh_left_gap(y);
    refresh_right_gap(y);
}

void gap_right_rotate(gap_node* y, gap_node** root)
{
    gap_node* x = y->left;
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

    refresh_left_gap(x);
    refresh_right_gap(x);
    refresh_left_gap(y);
    refresh_right_gap(y);
}

void gap_insert_fixup(gap_node* z, gap_node** root)
{
    while (z->prev && z->prev->isRed)
    {
        if (z->prev == z->prev->prev->left)
        {
            gap_node* y = z->prev->prev->right;

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
                gap_left_rotate(z, root);
            }
            else
            {
                z->prev->isRed = false;
                if (z->prev->prev)
                {
                    z->prev->prev->isRed = true;
                    gap_right_rotate(z->prev->prev, root);
                }
            }
        }
        else
        {
            gap_node* y = z->prev->prev->left;

            if (y && y->isRed)
            {
                z->prev->isRed = false;
                y->isRed = false;
                z->prev->prev->isRed = true;
                z = z->prev->prev;
            }
            else if (z == z->prev->prev)
            {
                z = z->prev;
                gap_right_rotate(z, root);
            }
            else
            {
                z->prev->isRed = false;
                if (z->prev->prev)
                {
                    z->prev->prev->isRed = true;
                    gap_left_rotate(z->prev->prev, root);
                }
            }
        }
    }
}

void gap_insert(gap_node** root, int value)
{
    gap_node* current = *root;
    gap_node* trailing = NULL;

    do
    {
        trailing = current;
        if (current->key > value)
            current = current->left;
        else
            current = current->right;
    } while (current);
    
    current = malloc(sizeof(gap_node));
    current->isRed = true;
    current->key = value;
    current->left = NULL;
    current->left_gap = value;
    current->prev = trailing;
    current->right = NULL;
    current->right_gap = value;

    if (trailing->key > value)
    {
        trailing->left = current;
        refresh_left_gap(trailing);
    }
    else
    {
        trailing->right = current;
        refresh_right_gap(trailing);
    }

    gap_insert_fixup(current, root);
    (*root)->isRed = false;
}

int min_gap(gap_node* head)
{
    if (head)
    {
        int sub_left = min_gap(head->left);
        int sub_right = min_gap(head->right);
        int left = head->left_gap > sub_left ? sub_left : head->left_gap;
        int right = head->right_gap > sub_right ? sub_right : head->right_gap;

        return left > right ? right : left;
    }
    else
        return 0x7fffffff;
}

int main(void)
{
    int data[7] = { 1,3,6,10,15,21,28 };

    gap_node* root = malloc(sizeof(gap_node));
    root->isRed = false;
    root->key = 1;
    root->left = NULL;
    root->left_gap = 1;
    root->prev = NULL;
    root->right = NULL;
    root->right_gap = 1;
    for (int i = 1; i < 7; ++i)
        gap_insert(&root, data[i]);
    
    min_gap(root);
    return 0;
}