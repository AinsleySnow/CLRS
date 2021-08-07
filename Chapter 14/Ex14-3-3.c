#include <stdio.h>
#include <stdlib.h>
#include "it/IntervalTree.h"

bool is_overlap(interval a, interval b)
{
    return b.high >= a.low || a.high >= b.low;
}

int_node* my_search(int_node* head, interval i)
{
    int_node* trailing = NULL;
    int_node* current = head;

    do
    {
        trailing = current;
        if (is_overlap(current->i, i))
            current = current->left;
        else
            return current->prev;
    } while (current);

    return trailing;
}

int main(void)
{
    interval data[10] =
    {
        {1,2}, {2,6}, {3,8}, {347, 900}, {2,57},
        {3,90}, {-2,4}, {6,8}, {90,100}, {1,10}
    };

    int_node* root = malloc(sizeof(int_node));
    root->i = data[0];
    root->isRed = false;
    root->left = NULL;
    root->right = NULL;
    root->prev = NULL;

    int_build(&root, data + 1, 9);

    int_node* ans = my_search(root, {0,2});
    printf("%d %d", ans->i.low, ans->i.high);

    return 0;
}