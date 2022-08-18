#include "RedBlackTree.h"
#include <stdlib.h>
#include <stdio.h>

rbt_node nil = {
    &nil, &nil, &nil,
    false, 0
};

void rb_left_rotate(rbt_node* x, rbt_node** root)
{
    rbt_node* y = x->right;
    x->right = y->left;
    
    if (y->left != &nil)
        y->left->prev = x;
    
    y->prev = x->prev;
    if (x->prev != &nil)
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

void rb_right_rotate(rbt_node* y, rbt_node** root)
{
    rbt_node* x = y->left;
    y->left = x->right;

    if (x->right != &nil)
        x->right->prev = y;
    
    x->prev = y->prev;
    if (y->prev != &nil)
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
}

void rb_insert_fixup(rbt_node* z, rbt_node** root)
{
    while (z->prev && z->prev->isRed)
    {
        if (z->prev == z->prev->prev->left)
        {
            rbt_node* y = z->prev->prev->right;

            if (y->isRed)
            {
                z->prev->isRed = false;
                y->isRed = false;
                z->prev->prev->isRed = true;
                z = z->prev->prev;
            }
            else if (z == z->prev->right)
            {
                z = z->prev;
                rb_left_rotate(z, root);
            }
            else
            {
                z->prev->isRed = false;
                z->prev->prev->isRed = true;
                rb_right_rotate(z->prev->prev, root);
                
            }
        }
        else
        {
            rbt_node* y = z->prev->prev->left;

            if (y->isRed)
            {
                z->prev->isRed = false;
                y->isRed = false;
                z->prev->prev->isRed = true;
                z = z->prev->prev;
            }
            else if (z == z->prev->left)
            {
                z = z->prev;
                rb_right_rotate(z, root);
            }
            else
            {
                z->prev->isRed = false;
                if (z->prev->prev)
                {
                    z->prev->prev->isRed = true;
                    rb_left_rotate(z->prev->prev, root);
                }
            }
        }
    }
}

void rb_insert(rbt_node** root, int value)
{
    rbt_node* trailing = &nil;
    rbt_node* current = *root;

    while (current != &nil)
    {
        trailing = current;
        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }

    rbt_node* temp = NULL;
    if (value < trailing->value)
    {
        trailing->left = malloc(sizeof(rbt_node));
        temp = trailing->left;
    }
    else
    {
        trailing->right = malloc(sizeof(rbt_node));
        temp = trailing->right;
    }

    temp->isRed = true;
    temp->left = &nil;
    temp->prev = trailing;
    temp->right = &nil;
    temp->value = value;

    rb_insert_fixup(temp, root);
    (*root)->isRed = false;
}

static rbt_node* tree_minimun(rbt_node* node)
{
    rbt_node* current = node;
    while (current->left != &nil)
        current = current->left;
    return current;
}

void rb_transplant(rbt_node** root, rbt_node* u, rbt_node* v)
{
    if (u->prev == &nil)
        *root = v;
    else if (u == u->prev->left)
        u->prev->left = v;
    else
        u->prev->right = v;
    if (v != &nil)
        v->prev = u->prev;
}

void rb_delete_fixup(rbt_node** root, rbt_node* x)
{
    while (x != *root && !x->isRed)
    {
        if (x == x->prev->left)
        {
            rbt_node* w = x->prev->right;
            if (w->isRed)
            {
                w->isRed = false;
                x->prev->isRed = true;
                rb_left_rotate(x->prev, root);
                w = x->prev->right;
            }
            else if (!w->left->isRed && !w->right->isRed)
            {
                if (w != &nil)
                    w->isRed = true;
                x = x->prev;
            }
            else if (!w->right->isRed)
            {
                w->left->isRed = false;
                w->isRed = true;
                rb_right_rotate(w, root);
                w = x->prev->right;
            }
            else
            {
                w->isRed = x->prev->isRed;
                x->prev->isRed = false;
                w->right->isRed = false;
                rb_left_rotate(x->prev, root);
                x = *root;                
            }
        }
        else
        {
            rbt_node* w = x->prev->left;
            if (w->isRed)
            {
                w->isRed = false;
                x->prev->isRed = true;
                rb_right_rotate(x->prev, root);
                w = x->prev->left;
            }
            else if (!w->right->isRed && !w->left->isRed)
            {
                if (w != &nil)
                    w->isRed = true;
                x = x->prev;
            }
            else if (!w->left->isRed)
            {
                w->right->isRed = false;
                w->isRed = true;
                rb_left_rotate(w, root);
                w = x->prev->left;
            }
            else
            {
                w->isRed = x->prev->isRed;
                x->prev->isRed = false;
                w->left->isRed = false;
                rb_right_rotate(x->prev, root);
                x = *root;                
            }
        }
    }

    x->isRed = false;
}

void rb_delete(rbt_node** root, rbt_node* z)
{
    rbt_node* y = z;
    rbt_node* x = &nil;
    bool is_y_red = y->isRed;

    if (z->left == &nil)
    {
        x = z->right;
        rb_transplant(root, z, z->right);
    }
    else if (z->right == &nil)
    {
        x = z->left;
        rb_transplant(root, z, z->left);
    }
    else
    {
        y = tree_minimun(z->right);
        is_y_red = y->isRed;
        x = y->right;
        if (y->prev == z)
            x->prev = y;
        else
        {
            rb_transplant(root, y, y->right);
            y->right = z->right;
            y->right->prev = y;
        }
        rb_transplant(root, z, y);
        y->left = z->left;
        y->left->prev = y;
        y->isRed = z->isRed;
    }
    
    if (!y->isRed)
        rb_delete_fixup(root, x);
}

void rbt_delete(rbt_node** head)
{
    if (*head != &nil)
    {
        rbt_delete(&((*head)->left));
        rbt_delete(&((*head)->right));
        free(*head);
        *head = &nil;
    }
}

void rbt_build(rbt_node** root, int* data, int size)
{
    for (int i = 0; i < size; ++i)
        rb_insert(root, data[i]);
}