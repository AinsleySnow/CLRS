#include <stdio.h>
#include <stdlib.h>
#include "List\List.h"

#define SIZE 4 // since the biggest in-degree is rather small

typedef struct graph_node
{
    int index;
    int in_deg;
    int adj_len;
    list_node* where;
    struct graph_node** adj;
} graph_node;

typedef graph_node* pnode;
typedef graph_node* vertex_list;
typedef graph_node** adjacency_list;

void extract(list_node* node, list* l)
{
    if (node->next)
        node->next->prev = node->prev;
    if (node->prev)
        node->prev->next = node->next;
    if (l->head == node)
        l->head = node->next;
    if (l->tail == node)
        l->tail = node->prev;
}

void insert(list_node* node, list* l)
{
    if (!l->head && !l->tail)
    {
        l->head = node;
        l->tail = node;
    }
    else
    {
        node->prev = l->tail;
        node->next = NULL;
        l->tail->next = node;
        l->tail = node;
    }
}

list topological_sort(vertex_list vl, int n)
{
    list lists[SIZE] = {
        { NULL, NULL }, { NULL, NULL },
        { NULL, NULL }, { NULL, NULL }
    };
    list result = { NULL, NULL };

    for (int i = 0; i < n; ++i)
    {
        int adj_len = vl[i].adj_len;
        for (int j = 0; j < adj_len; ++j)
            vl[i].adj[j]->in_deg += 1;
    }

    for (int i = 0; i < n; ++i)
    {
        list_insert_to_head(lists + vl[i].in_deg, vl + i);
        vl[i].where = lists[vl[i].in_deg].head;
    }

    list_node* current = lists[0].head;
    while (current)
    {      
        pnode u = (pnode)current->content;
        for (int i = 0; i < u->adj_len; ++i)
        {
            u->adj[i]->in_deg -= 1;
            list_node* node = u->adj[i]->where;
            extract(node, lists + u->adj[i]->in_deg + 1);
            insert(node, lists + u->adj[i]->in_deg);
        }
        
        list_node* temp = current;
        current = current->next;
        extract(temp, lists + 0);
        insert(temp, &result);
    }

    return result;
}

vertex_list build_graph()
{
    vertex_list vl = calloc(14, sizeof(graph_node));

    vl[0].index = 0;
    vl[0].adj = calloc(3, sizeof(pnode));
    vl[0].adj_len = 3;
    vl[0].adj[0] = vl + 4;
    vl[0].adj[1] = vl + 5;
    vl[0].adj[2] = vl + 11;

    vl[1].index = 1;
    vl[1].adj = calloc(3, sizeof(pnode));
    vl[1].adj_len = 3;
    vl[1].adj[0] = vl + 2;
    vl[1].adj[1] = vl + 4;
    vl[1].adj[2] = vl + 8;

    vl[2].index = 2;
    vl[2].adj = calloc(3, sizeof(pnode));
    vl[2].adj_len = 3;
    vl[2].adj[0] = vl + 5;
    vl[2].adj[1] = vl + 6;
    vl[2].adj[2] = vl + 9;

    vl[3].index = 3;
    vl[3].adj = calloc(3, sizeof(pnode));
    vl[3].adj_len = 3;
    vl[3].adj[0] = vl + 2;
    vl[3].adj[1] = vl + 6;
    vl[3].adj[2] = vl + 13;

    vl[4].index = 4;
    vl[4].adj = calloc(1, sizeof(pnode));
    vl[4].adj_len = 1;
    vl[4].adj[0] = vl + 7;

    vl[5].index = 5;
    vl[5].adj = calloc(2, sizeof(pnode));
    vl[5].adj_len = 2;
    vl[5].adj[0] = vl + 8;
    vl[5].adj[1] = vl + 12;

    vl[6].index = 6;
    vl[6].adj = calloc(1, sizeof(pnode));
    vl[6].adj_len = 1;
    vl[6].adj[0] = vl + 5;

    vl[7].index = 7;

    vl[8].index = 8;
    vl[8].adj = calloc(1, sizeof(pnode));
    vl[8].adj_len = 1;
    vl[8].adj[0] = vl + 7;

    vl[9].index = 9;
    vl[9].adj = calloc(2, sizeof(pnode));
    vl[9].adj_len = 2;
    vl[9].adj[0] = vl + 10;
    vl[9].adj[1] = vl + 11;

    vl[10].index = 10;
    vl[10].adj = calloc(1, sizeof(pnode));
    vl[10].adj_len = 1;
    vl[10].adj[0] = vl + 13;

    vl[11].index = 11;

    vl[12].index = 12;
    vl[12].adj = calloc(1, sizeof(pnode));
    vl[12].adj_len = 1;
    vl[12].adj[0] = vl + 9;

    vl[13].index = 13;

    return vl;
}

void delete_graph(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
        if (vl[i].adj)
            free(vl[i].adj);
    free(vl);
}

int main(void)
{
    vertex_list vl = build_graph();
    list topo = topological_sort(vl, 14);

    for (list_node* n = topo.head; n; n = n->next)
        printf("%d ", ((pnode)n->content)->index);

    delete_graph(vl, 14);
    return 0;
}