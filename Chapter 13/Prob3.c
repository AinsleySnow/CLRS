/*
*   Solution to Problem 13-3, section b and c.
*   And more importantly, a complete implementation of avl tree!
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct avl_node
{
    struct avl_node* prev;
    struct avl_node* left;
    struct avl_node* right;
    int factor;
    int key;
} avl_node;

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

    if (y->factor > 0)
        x->factor += 1;
    else
        x->factor += -(y->factor) + 1;
    // x->factor += ((-y->factor) & (y->factor >> 31)) + 1;
    if (x->factor > 0)
        y->factor += 1;
    else
        y->factor += x->factor + 1;
    // y->factor += (x->factor & (x->factor >> 31)) + 1;
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

    if (x->factor < 0)
        y->factor -= 1;
    else
        y->factor -= x->factor + 1;
    // y->factor -= (~(x->factor >> 31) & x->factor) + 1;
    if (y->factor > 0)
        x->factor -= 1;
    else
        x->factor += y->factor - 1;
    // x->factor += (~(y->factor >> 31) & y->factor) - 1;
}

void avl_balance(avl_node* x, avl_node** root)
{
    if (x->factor == 2 && x->left->factor == 1)
        avl_right_rotate(x, root);
    else if (x->factor == 2 && x->left->factor == -1)
    {
        avl_left_rotate(x->left, root);
        avl_right_rotate(x, root);
    }
    else if (x->factor == -2 && x->right->factor == -1)
        avl_left_rotate(x, root);
    else
    {
        avl_right_rotate(x->right, root);
        avl_left_rotate(x, root);
    }
}

void avl_insert_fixup(avl_node* x, avl_node** root)
{
    do
    {
        if (x == x->prev->left)
            x->prev->factor++;
        else
            x->prev->factor--;

        x = x->prev;
    } while (x->prev && (x->factor == 1 || x->factor == -1));

    if (x->factor == 2 || x->factor == -2)
        avl_balance(x, root);
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
    } while (current);

    current = calloc(1, sizeof(avl_node));
    current->key = key;
    current->prev = trailing;

    if (trailing->key > key)
        trailing->left = current;
    else
        trailing->right = current;

    avl_insert_fixup(current, root);
}

avl_node* tree_min(avl_node* x)
{
    while (x->left)
        x = x->left;
    return x;
}

void transplant(avl_node* u, avl_node* v, avl_node** root)
{
    if (u->prev)
    {
        if (u == u->prev->left)
            u->prev->left = v;
        else
            u->prev->right = v;
    }
    else
        *root = v;

    if (v)
        v->prev = u->prev;
}

void avl_delete_fixup(avl_node* x, avl_node** root)
{
    while (x->prev && !x->factor && x->factor != 2 && x->factor != -2)
    {
        if (x == x->prev->left)
            x->prev->factor--;
        else
            x->prev->factor++;
        
        x = x->prev;
    }

    if (x->factor == 2 || x->factor == -2)
        avl_balance(x, root);
}

void avl_delete(avl_node* z, avl_node** root)
{
    avl_node* x = NULL;

    if (!z->left && !z->right)
    {
        if (z == z->prev->left)
            z->prev->factor--;
        else
            z->prev->factor++;

        x = z->prev;
    }
    else if (!z->right)
    {
        transplant(z, z->left, root);
        z->left->factor = 0;
        x = z->left;
    }
    else
    {
        avl_node* succ = tree_min(z->right);
        if (succ->prev != z)
        {
            transplant(succ, succ->right, root);
            succ->right = z->right;
            succ->right->prev = succ;

            succ->prev->factor--;
            x = succ->prev;
        }
        else
        {
            z->right->factor = z->factor - 1;
            x = z->right;
        }
            
        transplant(z, succ, root);
        succ->left = z->left;
        succ->left->prev = succ;
    }

    avl_delete_fixup(x, root);
}

avl_node* avl_search(avl_node* head, int key)
{
    avl_node* current = head;
    while (current)
    {
        if (current->key == key)
            return current;
        
        if (current->key > key)
            current = current->left;
        else
            current = current->right;
    }

    return NULL;
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
        printf("Level %d: %d, factor = %d\n", level, head->key, head->factor);
        avl_preorder_walk(head->left, level + 1);
        avl_preorder_walk(head->right, level + 1);
    }
}

int main(void)
{
    avl_node* root1 = calloc(1, sizeof(avl_node));

    int data1[10] = { 4, 7, 3, 1, 5, 6, 2, 8, 10, 9 };
    build_avl_tree(&root1, data1, 10);

    printf("How the tree looks like after all these nodes are inserted into it:\n");
    avl_preorder_walk(root1, 0);

    avl_node* node = avl_search(root1, 4);
    avl_delete(node, &root1);
    free(node);
    printf("How the tree looks like after a node was deleted from it:\n");
    avl_preorder_walk(root1, 0);
    
    delete_avl_tree(&root1);

    return 0;
}