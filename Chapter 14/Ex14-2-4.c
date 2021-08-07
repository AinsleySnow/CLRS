#include "../Chapter 13/rbt/RedBlackTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

rbt_node* rb_min(rbt_node* head)
{
    rbt_node* trailing = NULL;
    rbt_node* current = head;

    while (current)
    {
        trailing = current;
        current = current->left;
    }

    return trailing;
}

rbt_node* rb_successor(rbt_node* head)
{
    if (head->right)
        return rb_min(head->right);
    
    rbt_node* trailing = head;
    head = head->prev;
    while (head && trailing == head->right)
    {
        trailing = head;
        head = head->prev;
    }

    return head;
}

rbt_node* rb_approximate_search(rbt_node* root, int key, bool isLeft)
{
    rbt_node* current = root;
    rbt_node* trailing = NULL;

    while (true)
    {
        trailing = current;

        if (current->value == key)
            return current;
        else if (current->value > key)
            current = current->left;
        else if (current->value < key)
            current = current->right;

        if (!current)
            break;
        
        if ((isLeft && current->value < key) || 
            (!isLeft && current->value > key))
                return trailing;
    }
    return trailing;
}

void rb_enumerate(rbt_node* head, int a, int b)
{
    if (head->value > b)
        rb_enumerate(head->left, a, b);
    else if (head->value < a)
        rb_enmuerate(head->right, a, b);
    else
    {
        rbt_node* nodeA = rb_approximate_search(head, a, true);
        rbt_node* nodeB = rb_approximate_search(head, b, false);
        while (nodeA != nodeB)
        {
            printf("%4d", nodeA->value);
            nodeA = rb_successor(nodeA);
        }
        printf("%4d", nodeB->value);
    }
}

int main(void)
{
    srand(time(NULL));

    int* data = malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; ++i)
        data[i] = rand() % 200;

    rbt_node* root = malloc(sizeof(rbt_node));
    rbt_build(&root, data, 100);

    int low = rand() % 30;
    int high = low + rand() % 170;

    printf("Data in red-black tree:\n");
    for (int i = 0, j = 0; i < 100; ++i)
    {
        printf("%4d", data[i]);
        ++j;
        if (!(j % 4))
        {
            j = 0;
            printf("\n");
        }
    }

    printf("\na = %3d, b = %3d\n", low, high);
    printf("\nResult of rb_enumerate():\n");
    rb_enumerate(head, low, high);

    rbt_delete(&root);
    root = NULL;
    return 0;
}