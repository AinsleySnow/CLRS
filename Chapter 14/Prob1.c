#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct endpoint
{
    struct endpoint* left;
    struct endpoint* right;
    struct endpoint* prev;
    int key;
    bool isRed;
    bool isLeft;
} endpoint;

typedef struct interval
{
    int low;
    int high;
} interval;

void ep_insert_interval(endpoint** root, interval i);
endpoint* find_pom(endpoint* root);

int main(void)
{
    interval invls[10];
    srand(time(NULL));

    for (int i = 0; i < 10; ++i)
    {
        int low = rand() % 100;
        int high = low + rand() % 100;
        invls[i].low = low;
        invls[i].high = high;
    }

    endpoint* root = NULL;
    for (int i = 0; i < 10; ++i)
        ep_insert_interval(&root, invls[i]);

    printf("result = %d\n", find_pom(root)->key);
    for (int i = 0; i < 10; ++i)
        printf("%4d-->%4d", invls[i].low, invls[i].high);

    return 0;
}

void ep_left_rotate(endpoint* x, endpoint** root)
{
    endpoint* y = x->right;
    x->right = y->left;

    if (y->left)
        y->left->prev = x;
    
    y->prev = x->prev;
    if (x->prev)
    {
        if (x == x->prev->prev)
            x->prev->left = y;
        else
            x->prev->right = y;
    }
    else
        *root = y;
    
    x->prev = y;
    y->left = x;
}

void ep_right_rotate(endpoint* y, endpoint** root)
{
    endpoint* x = y->left;
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
    
    y->prev = x;
    x->right = y;
}

void ep_insert_fixup(endpoint* z, endpoint** root)
{
    while (z->prev && z->prev->isRed)
    {
        if (z->prev == z->prev->prev->left)
        {
            endpoint* y = z->prev->prev->right;

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
                ep_left_rotate(z, root);
            }
            else
            {
                z->prev->isRed = false;
                if (z->prev->prev)
                {
                    z->prev->prev->isRed = true;
                    ep_right_rotate(z->prev->prev, root);
                }
            }
        }
        else
        {
            endpoint* y = z->prev->prev->left;

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
                ep_right_rotate(z, root);
            }
            else
            {
                z->prev->isRed = false;
                if (z->prev->prev)
                {
                    z->prev->prev->isRed = true;
                    ep_left_rotate(z->prev->prev, root);
                }
            }
        }
    }
}

void ep_insert_point(endpoint** root, int value, bool isLeft)
{
    if (*root == NULL)
    {
        *root = malloc(sizeof(endpoint));
        (*root)->isLeft = isLeft;
        (*root)->isRed = false;
        (*root)->key = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root)->prev = NULL;
        return;
    }

    endpoint* trailing = NULL;
    endpoint* current = *root;

    while(current)
    {
        trailing = current;
        if (value < current->key)
            current = current->left;
        else
            current = current->right;
    }

    endpoint* temp = NULL;
    if (value < trailing->key)
    {
        trailing->left = malloc(sizeof(endpoint));
        temp = trailing->left;
    }
    else
    {
        trailing->right = malloc(sizeof(endpoint));
        temp = trailing->right;
    }

    temp->isRed = true;
    temp->left = NULL;
    temp->prev = trailing;
    temp->right = NULL;
    temp->key = value;
    temp->isLeft = isLeft;

    ep_insert_fixup(temp, root);
    (*root)->isRed = false;
}

void ep_insert_interval(endpoint** root, interval i)
{
    ep_insert_point(root, i.low, true);
    ep_insert_point(root, i.high, false);
}

endpoint* ep_min(endpoint* head)
{
    endpoint* trailing = NULL;
    endpoint* current = head;

    while (current)
    {
        trailing = current;
        current = current->left;
    }
    return trailing;
}

endpoint* ep_successor(endpoint* node)
{
    if (node->right)
        return ep_min(node->right);
    
    endpoint* trailing = node;
    node = node->prev;
    while (node && trailing == node->right)
    {
        trailing = node;
        node = node->prev;
    }
    return node;
}

endpoint* find_pom(endpoint* root)
{
    endpoint* current = root;
    endpoint* trailing = NULL;

    do
    {
        trailing = current;
        current = ep_successor(current);
        if (!current->isLeft)
            break;
    } while (current);
    
    return trailing;
}