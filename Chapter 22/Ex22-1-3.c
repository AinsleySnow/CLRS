#include <stdlib.h>
#include <stdio.h>

typedef struct list_node
{
    void* content;
    struct list_node* next;
} list_node;

typedef struct graph_node
{
    int index;
    int adj_size;
    list_node* adj;
} graph_node;

typedef graph_node* vertex_list;
typedef graph_node* pnode;
typedef list_node* adjacency_list;

void append(adjacency_list* adj, void* content)
{
    list_node* current = *adj;
    list_node* trailing = current;
    while (current)
    {
        trailing = current;
        current = current->next;
    }

    current = calloc(1, sizeof(list_node));
    current->content = content;
    if (trailing)
        trailing->next = current;
    else
        *adj = current;
}

void transpose_adjacency_martrix(int n, int matrix[][n])
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            int temp = matrix[i][j];
            *(&matrix[i][j]) = matrix[j][i];
            *(&matrix[j][i]) = temp;
        }
    }
}

void transpose_adjacency_list(vertex_list vl, vertex_list out, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int m = vl[i].adj_size;
        for (int j = 0; j < m; ++j)
        {
            int index = ((graph_node*)(vl[i].adj[j].content))->index;
            append(&out[index].adj, vl + i);
        }
    }
}

vertex_list bulid_graph()
{
    vertex_list g = calloc(6, sizeof(graph_node));
    g[0].index = 0;
    g[0].adj = calloc(2, sizeof(pnode));
    g[0].adj_size = 2;
    g[0].adj[0].content = g + 1;
    g[0].adj[0].next = g[0].adj + 1;
    g[0].adj[1].content = g + 3;

    g[1].adj = calloc(1, sizeof(pnode));
    g[1].index = 1;
    g[1].adj_size = 1;
    g[1].adj[0].content = g + 4;

    g[2].adj = calloc(2, sizeof(pnode));
    g[2].index = 2;
    g[2].adj_size = 2;
    g[2].adj[0].content = g + 4;
    g[2].adj[0].next = g[2].adj + 1;
    g[2].adj[1].content = g + 5;

    g[3].adj = calloc(1, sizeof(pnode));
    g[3].index = 3;
    g[3].adj_size = 1;
    g[3].adj[0].content = g + 2;

    g[4].adj = calloc(1, sizeof(pnode));
    g[4].index = 4;
    g[4].adj_size = 1;
    g[4].adj[0].content = g;

    g[5].adj = calloc(1, sizeof(pnode));
    g[5].index = 5;
    g[5].adj_size = 1;
    g[5].adj[0].content = g + 5;

    return g;
}

int main(void)
{
    int matrix[][6] = {
        { 0, 1, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 1, 1 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 1 }
    };

    transpose_adjacency_martrix(6, matrix);
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");


    vertex_list vl = bulid_graph();
    vertex_list out = calloc(6, sizeof(graph_node));
    for (int i = 0; i < 6; ++i)
        out[i].index = i;
    transpose_adjacency_list(vl, out, 6);
    
    for (int i = 0; i < 6; ++i)
    {
        printf("%d:\n    ", out[i].index);
        for (list_node* current = out[i].adj; current; current = current->next)
            printf("%d ", ((graph_node*)(current->content))->index);
        printf("\n");
    }

    return 0;
}