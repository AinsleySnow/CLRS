#include <stdio.h>
#include <stdlib.h>
#include "List\List.h"

typedef enum color
{
    white,
    black,
    gray
} color;

typedef struct graph_node
{
    int index;
    int adj_len;
    unsigned int ancestors;
    color c;
    struct graph_node** adj;
} graph_node;

typedef graph_node* pnode;
typedef graph_node* vertex_list;
typedef graph_node** adjacency_list;

list topo_dfs_visit(pnode u)
{
    list l = { NULL, NULL };
    u->c = gray;
    int n = u->adj_len;
    for (int i = 0; i < n; ++i)
    {
        pnode v = u->adj[i];
        if (v->c == white)
        {
            list temp = topo_dfs_visit(v);
            if (!l.head && !l.tail)
                l = temp;
            else if (temp.head && temp.tail)
            {
                l.head->prev = temp.tail;
                temp.tail->next = l.head;
                l.head = temp.head;
            }
        }
    }
    u->c = black;
    list_insert_to_head(&l, u);
    return l;
}

list topo_dfs(vertex_list vl, int n)
{
    list l = { NULL, NULL };
    for (int i = 0; i < n; ++i)
        vl[i].c = white;

    for (int i = 0; i < n; ++i)
    {
        if (vl[i].c == white)
        {
            list temp = topo_dfs_visit(vl + i);
            if (!l.head && !l.tail)
                l = temp;
            else if (temp.head && temp.tail)
            {
                l.head->prev = temp.tail;
                temp.tail->next = l.head;
                l.head = temp.head;
            }
        }
    }

    return l;
}

vertex_list build_graph1()
{
    vertex_list g = calloc(6, sizeof(graph_node));
    for (int i = 0; i < 6; ++i)
        g[i].index = i;
    
    g[0].adj_len = 2;
    g[0].adj = calloc(2, sizeof(pnode));
    g[0].adj[0] = &g[1];
    g[0].adj[1] = &g[3];

    g[1].adj = calloc(1, sizeof(pnode));
    g[1].adj_len = 1;
    g[1].adj[0] = &g[4];

    g[2].adj = calloc(2, sizeof(pnode));
    g[2].adj_len = 2;
    g[2].adj[0] = &g[4];
    g[2].adj[1] = &g[5];

    g[3].adj = calloc(1, sizeof(pnode));
    g[3].adj_len = 1;
    g[3].adj[0] = &g[2];

    g[4].adj = calloc(1, sizeof(pnode));
    g[4].adj_len = 1;
    g[4].adj[0] = &g[0];

    g[5].adj = calloc(1, sizeof(pnode));
    g[5].adj_len = 1;
    g[5].adj[0] = &g[5];

    return g;
}

vertex_list build_graph2()
{
    vertex_list g = calloc(6, sizeof(graph_node));
    for (int i = 0; i < 6; ++i)
        g[i].index = i;
    
    g[0].adj = calloc(2, sizeof(pnode));
    g[0].adj_len = 2;
    g[0].adj[0] = &g[1];
    g[0].adj[1] = &g[2];

    g[1].adj = calloc(2, sizeof(pnode));
    g[1].adj_len = 2;
    g[1].adj[0] = &g[3];
    g[1].adj[1] = &g[4];

    g[2].adj = calloc(1, sizeof(pnode));
    g[2].adj_len = 1;
    g[2].adj[0] = &g[5];

    return g;
}

void print_graph(list l)
{
    list_node* current = l.head;
    while (current)
    {
        printf("%d ", ((graph_node*)current->content)->index);
        current = current->next;
    }
}

void delete_graph(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
        free(vl[i].adj);
    free(vl);
}

bool is_singly_connected(list l)
{
    list_node* current = l.head;
    while (current)
    {
        pnode u = (pnode)current->content;
        for (int j = 0; j < u->adj_len; ++j)
        {
            unsigned int xor = u->adj[j]->ancestors ^ u->ancestors;
            u->adj[j]->ancestors += u->ancestors;
            if (u->adj[j]->ancestors != xor)
                return false;

            u->adj[j]->ancestors |= 1 << u->index;
        }
        current = current->next;
    }

    return true;
}

int main(void)
{
    vertex_list vl[] = { build_graph1(), build_graph2() };
    list l[] = { topo_dfs(vl[0], 6), topo_dfs(vl[1], 6) };

    for (int i = 0; i < 2; ++i)
    {
        bool isSinglyConnected = is_singly_connected(l[i]);
        printf("Graph %d is %s.\n", i, isSinglyConnected ? "singly connected" : "not singly connected"); 
        delete_graph(vl[i], 6);
        list_free(&l[i]);
    }

    return 0;
}