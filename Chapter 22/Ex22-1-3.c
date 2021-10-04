#include <stdlib.h>
#include <stdio.h>

typedef struct graph_node
{
    int index;
    adjacency_list adj;
} graph_node;

typedef struct list_node
{
    void* content;
    list_node* next;
} list_node;

typedef graph_node* vertex_list;
typedef graph_node* pnode;
typedef list_node* adjacency_list;

void append(adjacency_list adj, void* content)
{
    list_node* current = adj;
    list_node* trailing = NULL;
    while (current)
    {
        trailing = current;
        current = current->next;
    }

    current = calloc(1, sizeof(list_node));
    current->content = content;
    trailing->next = current;
}

void transpose_adjacency_martrix(int** martrix)
{
    int m = sizeof(martrix) / sizeof(int*);
    int n = sizeof(*martrix) / sizeof(int);
    for (int i = 0; i < m; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            int temp = martrix[i][j];
            martrix[i][j] = martrix[j][i];
            martrix[j][i] = temp;
        }
    }
}

void transpose_adjacency_list(vertex_list vl, vertex_list out)
{
    int n = sizeof(vl) / sizeof(graph_node);

    for (int i = 0; i < n; ++i)
    {
        int m = sizeof(vl[i].adj) / sizeof(graph_node);
        for (int j = 0; j < m; ++j)
        {
            int index = ((graph_node*)(vl[i].adj[j].content))->index;
            append(out[index].adj, vl + i);
        }
    }
}

vertex_list bulid_graph()
{
    vertex_list g = calloc(6, sizeof(graph_node));
    g[0].adj = calloc(2, sizeof(pnode));
    g[0].adj[0].content = g + 1;
    g[0].adj[0].next = g[0].adj + 1;
    g[0].adj[1].content = g + 3;

    g[1].adj = calloc(1, sizeof(pnode));
    g[1].adj[0].content = g + 4;

    g[2].adj = calloc(2, sizeof(pnode));
    g[2].adj[0].content = g + 4;
    g[2].adj[0].next = g[2].adj + 1;
    g[2].adj[1].content = g + 5;

    g[3].adj = calloc(1, sizeof(pnode));
    g[3].adj[0].content = g + 2;

    g[4].adj = calloc(1, sizeof(pnode));
    g[4].adj[0].content = g;

    g[5].adj = calloc(1, sizeof(pnode));
    g[5].adj[0].content = g + 5;

    return g;
}

int main(void)
{
    int martrix[][6] = {
        { 0, 1, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 1, 1 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 1 }
    };

    transpose_adjacency_martrix(martrix);
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
            printf("%d ", martrix[i][j]);
        printf("\n");
    }
    printf("\n");

    vertex_list vl = bulid_graph();
    vertex_list out = calloc(6, sizeof(graph_node));
    transpose_adjacency_list(vl, out);
    
}