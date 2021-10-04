#include <stdlib.h>
#include <stdio.h>
#include "Queue\Queue.h"

typedef struct tree_node
{
    struct tree_node* prev;
    struct tree_node** children;
} tree_node;

int get_diameter(tree_node* head)
{
    queue q;
    enqueue(&q, head);
    tree_node* u = NULL;
    while (!is_empty(&q))
    {
        u = dequeue(&q);
        for (int i = 0; i < sizeof(u->children) / sizeof(tree_node*); ++i)
            enqueue(&q, u->children[i]);
    }

    int d = 0;
    while (u)
    {
        u = u->prev;
        ++d;
    }
    return d;
}

tree_node* build_tree()
{
    tree_node* head = calloc(1, sizeof(tree_node));
    head->children = calloc(2, sizeof(tree_node*));

    head->children[0] = calloc(1, sizeof(tree_node));
    head->children[0]->prev = head;
    head->children[0]->children = calloc(2, sizeof(tree_node*));
    head->children[0]->children[0] = calloc(1, sizeof(tree_node));
    head->children[0]->children[0]->prev = head->children[0];
    head->children[0]->children[1] = calloc(1, sizeof(tree_node));
    head->children[0]->children[1]->prev = head->children[0];
    *(head->children[0]->children[1]->children) = calloc(1, sizeof(tree_node));
    (*(head->children[0]->children[1]->children))->prev = head->children[0]->children[1];

    head->children[1] = calloc(1, sizeof(tree_node));

    return head;
}

void free_tree(tree_node* head)
{
    if (head->children)
        for (int i = 0; i < sizeof(head->children) / sizeof(tree_node*); ++i)
            free_tree(head->children[i]);
    
    free(head);
}

int main(void)
{
    tree_node* head = build_tree();
    printf("%d", get_diameter(head));
    free_tree(head);
    return 0;
}