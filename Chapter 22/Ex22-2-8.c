#include <stdlib.h>
#include <stdio.h>
#include "Queue\Queue.h"

typedef struct tree_node
{
    int chld_num;
    int d;
    struct tree_node* prev;
    struct tree_node** children;
} tree_node;

int get_diameter(tree_node* head)
{
    queue q = { NULL, NULL };
    enqueue(&q, head);
    tree_node* u = NULL;
    while (!is_empty(&q))
    {
        u = dequeue(&q);
        for (int i = 0; i < u->chld_num; ++i)
        {
            u->children[i]->d = u->d + 1;
            enqueue(&q, u->children[i]);
        }     
    }

    return u->d + 1;
}

tree_node* build_tree()
{
    tree_node* head = calloc(1, sizeof(tree_node));
    head->chld_num = 2;
    head->children = calloc(2, sizeof(tree_node*));

    head->children[0] = calloc(1, sizeof(tree_node));
    head->children[0]->prev = head;

    head->children[0]->children = calloc(2, sizeof(tree_node*));
    head->children[0]->chld_num = 2;
    head->children[0]->children[0] = calloc(1, sizeof(tree_node));
    head->children[0]->children[0]->prev = head->children[0];
    head->children[0]->children[1] = calloc(1, sizeof(tree_node));
    head->children[0]->children[1]->prev = head->children[0];
    
    head->children[0]->children[1]->children = calloc(1, sizeof(tree_node*));
    head->children[0]->children[1]->chld_num = 1;
    head->children[0]->children[1]->children[0] = calloc(1, sizeof(tree_node));
    head->children[0]->children[1]->children[0]->prev = head->children[0]->children[1];

    head->children[1] = calloc(1, sizeof(tree_node));

    return head;
}

void free_tree(tree_node* head)
{
    if (head->children)
        for (int i = 0; i < head->chld_num; ++i)
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