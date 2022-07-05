#include <stdio.h>
#include <stdlib.h>

typedef enum color
{
    white,
    black,
    gray
} color;

typedef struct graph_node
{
    int cc;
    int adj_len;
    color c;
    struct graph_node* pi;
    struct graph_node** adj;
} graph_node;

typedef graph_node* pnode;
typedef graph_node* vertex_list;
typedef graph_node** adjacency_list;

void dfs_visit(pnode u)
{   
    u->c = gray;
    int n = u->adj_len;
    for (int i = 0; i < n; ++i)
    {
        pnode v = u->adj[i];
        if (v->c == white)
        {
            v->pi = u;
            v->cc = u->cc;
            dfs_visit(v);
        }
    }
    u->c = black;
}

void dfs(vertex_list vl, int n)
{
    int cc = 0;
    for (int i = 0; i < n; ++i)
    {
        vl[i].c = white;
        vl[i].pi = NULL;
    }
    
    for (int i = 0; i < n; ++i)
    {
        if (vl[i].c == white)
        {
            vl[i].cc = cc;
            ++cc;
            dfs_visit(vl + i);
        }   
    }       
}

vertex_list build_graph1()
{
    // This graph has only one connected component.
    
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
    // This graph has two connected components.
    // It is adapted from figure 22.9(a) in Introduction to Algorithms.
    
    vertex_list g = calloc(8, sizeof(graph_node));
    g[0].adj = calloc(1, sizeof(pnode));
    g[0].adj_len = 1;
    g[0].adj[0] = &g[1];

    g[1].adj = calloc(2, sizeof(pnode));
    g[1].adj_len = 2;
    g[1].adj[0] = &g[4];
    g[1].adj[1] = &g[5];

    g[2].adj = calloc(2, sizeof(pnode));
    g[2].adj_len = 2;
    g[2].adj[0] = &g[3];
    g[2].adj[1] = &g[6];

    g[3].adj = calloc(2, sizeof(pnode));
    g[3].adj_len = 2;
    g[3].adj[0] = &g[2];
    g[3].adj[1] = &g[7];

    g[4].adj = calloc(2, sizeof(pnode));
    g[4].adj_len = 2;
    g[4].adj[0] = &g[0];
    g[4].adj[1] = &g[5];

    g[5].adj_len = 0;

    g[6].adj = calloc(1, sizeof(pnode));
    g[6].adj_len = 1;
    g[6].adj[0] = &g[7];

    g[7].adj = calloc(1, sizeof(pnode));
    g[7].adj_len = 1;
    g[7].adj[0] = &g[7];

    return g;
}

void print_graph(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("vertex %d:\n", i);
        printf("color = %d\n", vl[i].c);
        printf("pi = %d\n", vl[i].pi ? (int)(vl[i].pi - vl) : -1);
        printf("cc = %d\n", vl[i].cc);
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
    vertex_list vl = build_graph1();
    dfs(vl, 6);
    print_graph(vl, 6);
    delete_graph(vl, 6);

    printf("--------------------\n");

    vl = build_graph2();
    dfs(vl, 8);
    print_graph(vl, 8);
    delete_graph(vl, 8);

    return 0;
}