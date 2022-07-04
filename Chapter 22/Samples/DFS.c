#include <stdio.h>
#include <stdlib.h>

typedef enum color
{
    white,    
    gray,
    black
} color;

typedef struct graph_node
{
    int d;
    int f;
    int adj_len;
    color c;
    struct graph_node* pi;
    struct graph_node** adj;
} graph_node;

typedef graph_node* pnode;
typedef graph_node* vertex_list;
typedef graph_node** adjacency_list;

static int time = 0;

void dfs_visit(pnode u)
{
    time++;
    u->d = time;
    u->c = gray;
    int n = u->adj_len;
    for (int i = 0; i < n; ++i)
    {
        pnode v = u->adj[i];
        if (v->c == white)
        {
            v->pi = u;
            dfs_visit(v);
        }
    }
    u->c = black;
    time++;
    u->f = time;
}

void dfs(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
    {
        vl[i].c = white;
        vl[i].pi = NULL;
    }
    
    for (int i = 0; i < n; ++i)
        if (vl[i].c == white)
            dfs_visit((pnode)(vl + i));
}

vertex_list build_graph()
{
    vertex_list g = calloc(6, sizeof(graph_node));

    g[0].adj = calloc(2, sizeof(pnode));
    g[0].adj_len = 2;
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
    g[3].adj[0] = &g[1];

    g[4].adj = calloc(1, sizeof(pnode));
    g[4].adj_len = 1;
    g[4].adj[0] = &g[3];

    g[5].adj = calloc(1, sizeof(pnode));
    g[5].adj_len = 1;
    g[5].adj[0] = &g[5];

    return g;
}

void print_graph(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("vertex %d:\n", i);
        printf("d = %d, f = %d\n", vl[i].d, vl[i].f);
        printf("color = %d\n", vl[i].c);
        printf("pi = %d\n", vl[i].pi ? (int)(vl[i].pi - vl) : -1);
        printf("\n");
    }
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
    dfs(vl, 6);
    print_graph(vl, 6);

    delete_graph(vl, 6);
    return 0;
}