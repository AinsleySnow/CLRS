#include <stdio.h>
#include <stdlib.h>
#include "..\List\List.h"

typedef enum color
{
    white,
    gray,
    black
} color;

typedef struct graph_node
{
    int index;
    color c;
    int adj_len;
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

vertex_list build_graph()
{
    vertex_list g = calloc(9, sizeof(graph_node));

    g[0].adj = calloc(2, sizeof(pnode));
    g[0].index = 0;
    g[0].adj_len = 2;
    g[0].adj[0] = g + 1;
    g[0].adj[1] = g + 3;

    g[1].adj = calloc(1, sizeof(pnode));
    g[1].index = 1;
    g[1].adj_len = 1;
    g[1].adj[0] = g + 2;

    g[2].index = 2;

    g[3].adj = calloc(1, sizeof(pnode));
    g[3].index = 3;
    g[3].adj_len = 1;
    g[3].adj[0] = g + 2;

    g[4].index = 4;

    g[5].adj = calloc(2, sizeof(pnode));
    g[5].index = 5;
    g[5].adj_len = 2;
    g[5].adj[0] = g + 6;
    g[5].adj[1] = g + 7;

    g[6].adj = calloc(2, sizeof(pnode));
    g[6].index = 6;
    g[6].adj_len = 2;
    g[6].adj[0] = g + 3;
    g[6].adj[1] = g + 7;

    g[7].index = 7;

    g[8].adj = calloc(1, sizeof(pnode));
    g[8].index = 8;
    g[8].adj_len = 1;
    g[8].adj[0] = g + 7;

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

int main(void) // Topological sort
{
    vertex_list vl = build_graph();
    list l = dfs(vl, 9);
    print_graph(l);

    delete_graph(vl, 9);
    list_free(&l);
    return 0;
}