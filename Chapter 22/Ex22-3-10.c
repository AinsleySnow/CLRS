#include <stdio.h>
#include <stdlib.h>

#define INFINITE 0x7fffffff

typedef enum color
{
    white,
    black,
    gray
} color;

typedef struct graph_node
{
    int d;
    int f;
    color c;
    pnode pi;
    adjacency_list adj;
} graph_node;

typedef graph_node* pnode;
typedef graph_node* vertex_list;
typedef graph_node** adjacency_list;

static int time = 0;

void dfs(vertex_list vl)
{
    int n = sizeof(vl) / sizeof(graph_node);
    for (int i = 0; i < n; ++i)
    {
        vl[i].c = white;
        vl[i].pi = NULL;
    }
    
    for (int i = 0; i < n; ++i)
        if (vl[i].c == white)
            dfs_visit(vl, vl + i);
}

void dfs_visit(vertex_list vl, pnode u)
{
    time++;
    u->d = time;
    u->c = gray;
    int n = sizeof(u->adj) / sizeof(pnode);
    for (int i = 0; i < n; ++i)
    {
        pnode v = u->adj[i];
        if (v->c == white)
        {
            v->pi = u;
            dfs_visit(vl, v);
        }
    }
    u->c = black;
    time++;
    u->f = time;
}

vertex_list build_graph()
{
    vertex_list g = calloc(6, sizeof(graph_node));
    g[0].adj = calloc(2, sizeof(pnode));
    g[0].adj[0] = &g[1];
    g[0].adj[1] = &g[3];

    g[1].adj = calloc(1, sizeof(pnode));
    g[1].adj[0] = &g[4];

    g[2].adj = calloc(2, sizeof(pnode));
    g[2].adj[0] = &g[4];
    g[2].adj[1] = &g[5];

    g[3].adj = calloc(1, sizeof(pnode));
    g[3].adj[0] = &g[2];

    g[4].adj = calloc(1, sizeof(pnode));
    g[4].adj[0] = &g[0];

    g[5].adj = calloc(1, sizeof(pnode));
    g[5].adj[0] = &g[5];

    return g;
}

void print_graph(vertex_list vl)
{
    int n = sizeof(vl) / sizeof(graph_node);
    for (int i = 0; i < n; ++i)
    {
        printf("%dth vertex:\n");
        printf("distence = %d\n", vl[i].d);
        printf("color = %d\n", vl[i].c);
        printf("pi = %d\n", (int)(vl[i].pi - vl));
        printf("\n");
    }
}

void delete_graph(vertex_list vl)
{
    int n = sizeof(vl) / sizeof(graph_node);
    for (int i = 0; i < n; ++i)
        free(vl[i].adj);
    free(vl);
}

int main(void)
{
    vertex_list vl = build_graph();
    bfs(vl, vl + 1);
    print_graph(vl);

    delete_graph(vl);
    return 0;
}