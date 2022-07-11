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
    int count;
    int adj_len;
    int index;
    color c;
    struct graph_node* pi;
    struct graph_node** adj;
} graph_node;

typedef graph_node* pnode;
typedef graph_node* vertex_list;
typedef graph_node** adjacency_list;

list dfs_visit(pnode u)
{
    list l = { NULL, NULL };
    u->c = gray;
    int n = u->adj_len;
    for (int i = 0; i < n; ++i)
    {
        pnode v = u->adj[i];
        if (v->c == white)
        {
            list temp = dfs_visit(v);
            if (l.head)
            {
                l.head->prev = temp.tail;
                temp.tail->next = l.head;
                l.head = temp.head;
            }
            else
                l = temp;
        }
    }
    u->c = black;
    list_insert_to_head(&l, u);
    return l;
}

list dfs(vertex_list vl, int n)
{
    list l = { NULL, NULL };
    for (int i = 0; i < n; ++i)
        vl[i].c = white;

    for (int i = 0; i < n; ++i)
    {
        if (vl[i].c == white)
        {
            list temp = dfs_visit((pnode)(vl + i));
            if (l.head)
            {
                l.head->prev = temp.tail;
                temp.tail->next = l.head;
                l.head = temp.head;
            }
            else
                l = temp;
        }
    }

    return l;
}

int count(pnode s, pnode t, list topo)
{
    list_node* node = topo.head;
    for (; node; node = node->next)
        if (node->content == s)
            break;
    
    ((pnode)(node->content))->count = 1;

    for (; node; node = node->next)
    {
        pnode u = (pnode)node->content;
        for (int i = 0; i < u->adj_len; ++i)
            u->adj[i]->count += u->count;

        if (u == t)
            break;
    }

    return t->count;
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
        free(vl[i].adj);
    free(vl);
}

int main(void)
{
    vertex_list vl = build_graph();
    list l = dfs(vl, 14);

    printf("%d", count(vl + 3, vl + 9, l));
    delete_graph(vl, 14);
    return 0;
}