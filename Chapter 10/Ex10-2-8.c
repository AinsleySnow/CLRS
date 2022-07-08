#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct node
{
    uint64_t np;
    int v;
} node;

node* search(node* head, int key)
{
    node* next = NULL;
    node* prev = NULL;
    node* current = head;

    while (current)
    {
        if (current->v == key)
            return current;
        next = (node*)((uint64_t)prev ^ (uint64_t)current->np);
        prev = current;
        current = next;
    }

    return NULL;
}

void insert(node* head, int key)
{
    node* current = head;
    node* prev = NULL;
    node* next = NULL;
    while ((next = (node*)((uint64_t)(current->np) ^ (uint64_t)(prev))))
    {
        prev = current;
        current = next;
    }

    node* new_node = calloc(1, sizeof(node));
    new_node->np = (uint64_t)current;
    new_node->v = key;
    current->np ^= (uint64_t)new_node;
}

void delete(node* head, node* x)
{
    node* next = NULL;
    node* prev = NULL;
    node* current = head;

    while (current)
    {
        if (current == x)
            goto find;
        next = (node*)((uint64_t)prev ^ (uint64_t)current->np);
        prev = current;
        current = next;
    }
    return;

find:
    next = (node*)((uint64_t)prev ^ (uint64_t)current->np);
    next->np = next->np ^ (uint64_t)current ^ (uint64_t)prev;
    prev->np = prev->np ^ (uint64_t)current ^ (uint64_t)next;
    free(current);
}

void free_list(node* head)
{
    node* current = head;
    node* prev = NULL;
    node* temp = NULL;

    while (current)
    {
        temp = (node*)((uint64_t)(current->np) ^ (uint64_t)prev);
        prev = current;
        free(current);

        current = temp;
    }
}

int main(void)
{
    node* head = calloc(1, sizeof(node));
    head->v = 4;

    insert(head, 1);
    insert(head, 2);
    insert(head, 1000);
    insert(head, 387);
    insert(head, 2387498);

    node* ans_node = search(head, 9);
    if (ans_node)
    {
        printf("This line should not have been printed.\n");
        return 0;
    }

    ans_node = search(head, 1);
    printf("%d\n", ans_node->v);
    ans_node = search(head, 1000);
    printf("%d\n", ans_node->v);

    delete(head, ans_node);
    ans_node = search(head, 1000);
    if (ans_node)
    {
        printf("This line should not have been printed.\n");
        return 0;
    }

    free_list(head);

    return 0;
}