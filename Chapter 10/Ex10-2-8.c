#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    long np;
    int v;
}node;

node search(node* head, int key)
{
    node* next = head->np;
    node* current = NULL;

    do
    {
        current = next;
        if(current->v == key)
            return current;
        next = (node*)((long)next ^ head->np);
    }while(current);

    return {0, 0};
}

void insert(node* head, int key)
{
    node* x = malloc(sizeof(node));
    node* current = head;
    node* trailing = NULL;

    node* prev = 0;
    node* temp = NULL;
    while(temp = (node*)((long)(current->np) ^ prev))
    {
        prev = current;
        current = temp;
    }
    
    x->np = prev;
    x->v = key;
    current->np ^= (long)x;
}

void delete(node* head, node* x)
{
    node* current = (node*)head;
    node* next = (node*)head->np;
    node* prev = NULL;
    node* temp = NULL;

    while(current)
    {
        if(current == x)
        {
            prev = (node*)(current->np ^ (long)next);
            current = next;
            next = (node*)((long)next ^ current->np);
            prev->np = prev->np ^ (long)current;
            next->np = next->np ^ (long)current;
            next->np = next->np ^ (long)prev;
            return;
        }
        temp = (node*)((long)(current->np) ^ prev);
        prev = current
        current = temp;
    }    
}

int main(void)
{

}