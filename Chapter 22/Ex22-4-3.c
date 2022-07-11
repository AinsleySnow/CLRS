#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum color
{
    white,
    black,
    gray
} color;

typedef struct graph_node
{
    int adj_len;
    color c;
    struct graph_node* pi;
    struct graph_node** adj;
} graph_node;

typedef graph_node* pnode;
typedef graph_node* vertex_list;
typedef graph_node** adjacency_list;

bool dfs_visit(pnode u)
{
    u->c = gray;
    int n = u->adj_len;
    for (int i = 0; i < n; ++i)
    {
        pnode v = u->adj[i];
        if (v->c == black)
            return true; // terminate early so that 
                         // the number of edges traversed 
                         // always less than or equal that
                         // of vertice we have discovered.
        if (v->c == white)
        {
            v->pi = u;
            if(dfs_visit(v))
                return true;
        }
    }
    u->c = black;
    return false;
}

bool has_cycle(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
        if (vl[i].c == white)
            if(dfs_visit(vl + i))
                return true;

    return false;
}

vertex_list build_graph()
{
    vertex_list g = calloc(6, sizeof(graph_node));
    g[0].adj = calloc(2, sizeof(pnode));
    g[0].adj_len = 2;
    g[0].adj[0] = &g[1];
    g[0].adj[1] = &g[3];

    g[1].adj = calloc(2, sizeof(pnode));
    g[1].adj_len = 2;
    g[1].adj[0] = &g[0];
    g[1].adj[1] = &g[4];

    g[2].adj = calloc(2, sizeof(pnode));
    g[2].adj_len = 2;
    g[2].adj[0] = &g[4];
    g[2].adj[1] = &g[5];

    g[3].adj = calloc(1, sizeof(pnode));
    g[3].adj_len = 1;
    g[3].adj[0] = &g[0];

    g[4].adj = calloc(2, sizeof(pnode));
    g[4].adj_len = 2;
    g[4].adj[0] = &g[1];
    g[4].adj[1] = &g[2];

    g[5].adj = calloc(1, sizeof(pnode));
    g[5].adj_len = 1;
    g[5].adj[0] = &g[2];

    return g;
}

vertex_list build_graph2()
{
    vertex_list g = calloc(6, sizeof(graph_node));
    g[0].adj = calloc(3, sizeof(pnode));
    g[0].adj_len = 3;
    g[0].adj[0] = &g[1];
    g[0].adj[1] = &g[3];
    g[0].adj[2] = &g[4];

    g[1].adj = calloc(2, sizeof(pnode));
    g[1].adj_len = 2;
    g[1].adj[0] = &g[0];
    g[1].adj[1] = &g[4];

    g[2].adj = calloc(3, sizeof(pnode));
    g[2].adj_len = 3;
    g[2].adj[0] = &g[3];
    g[2].adj[1] = &g[4];
    g[2].adj[2] = &g[5];

    g[3].adj = calloc(2, sizeof(pnode));
    g[3].adj_len = 2;
    g[3].adj[0] = &g[0];
    g[3].adj[1] = &g[2];

    g[4].adj = calloc(4, sizeof(pnode));
    g[4].adj_len = 4;
    g[4].adj[0] = &g[0];
    g[4].adj[1] = &g[1];
    g[4].adj[2] = &g[2];
    g[4].adj[3] = &g[5];

    g[5].adj = calloc(2, sizeof(pnode));
    g[5].adj_len = 2;
    g[5].adj[0] = &g[2];
    g[5].adj[1] = &g[4];

    return g;
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
    vertex_list vl2 = build_graph2();

    printf("Graph 1 %s a cycle.\n", has_cycle(vl, 6) ? "has" : "doesn't have");
    printf("Graph 2 %s a cycle.", has_cycle(vl2, 6) ? "has" : "doesn't have");
    delete_graph(vl, 6);
    return 0;
}