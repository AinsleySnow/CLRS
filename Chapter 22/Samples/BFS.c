#include "../Queue/Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    color c;
    pnode pi;
    adjacency_list adj;
} graph_node;

typedef graph_node* pnode;
typedef graph_node* vertex_list;
typedef graph_node** adjacency_list;

void bfs(vertex_list graph, pnode source)
{
    int n = sizeof(graph) / sizeof(graph_node);
    for (int i = 0; i < n; ++i)
    {
        if (graph + i != source)
        {
            graph[i].c = white;
            graph[i].d = INFINITE;
            graph[i].pi = NULL;
        }
    }

    source->c = gray;
    source->d = 0;
    source->pi = NULL;

    queue q = { NULL, NULL };
    enqueue(&q, source);
    while (!is_empty(&q))
    {
        pnode u = dequeue(&q);
        int adj_len = sizeof(u->adj) / sizeof(pnode);
        for (int i = 0; i < adj_len; ++i)
        {
            pnode v = u->adj[i];
            if (v->c == white)
            {
                v->c = gray;
                v->d = u->d + 1;
                v->pi = u;
                enqueue(&q, v);
            }    
        }
        u->c = black;
    }
}

vertex_list build_graph()
{
    vertex_list g = calloc(8, sizeof(graph_node));
    g[0].adj = calloc(2, sizeof(pnode));
    g[0].adj[0] = &g[1];
    g[0].adj[1] = &g[4];

    g[1].adj = calloc(2, sizeof(pnode));
    g[1].adj[0] = &g[0];
    g[1].adj[1] = &g[5];

    g[2].adj = calloc(3, sizeof(pnode));
    g[2].adj[0] = &g[3];
    g[2].adj[1] = &g[5];
    g[2].adj[2] = &g[6];

    g[3].adj = calloc(3, sizeof(pnode));
    g[3].adj[0] = &g[2];
    g[3].adj[1] = &g[6];
    g[3].adj[2] = &g[7];

    g[4].adj = calloc(1, sizeof(pnode));
    g[4].adj[0] = &g[0];

    g[5].adj = calloc(3, sizeof(pnode));
    g[5].adj[0] = &g[1];
    g[5].adj[1] = &g[2];
    g[5].adj[2] = &g[6];

    g[6].adj = calloc(4, sizeof(pnode));
    g[6].adj[0] = &g[2];
    g[6].adj[1] = &g[3];
    g[6].adj[2] = &g[5];
    g[6].adj[3] = &g[7];

    g[7].adj = calloc(2, sizeof(pnode));
    g[7].adj[0] = &g[3];
    g[7].adj[1] = &g[6];

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