#include <stdio.h>
#include <stdlib.h>
#include "List\List.h"

#define generate_edge(u, v) (((u) << 16) | (v))

typedef enum color
{
    white,
    black
} color;

typedef struct graph_node
{
    int index;
    color c;
    graph_node** adj;
} graph_node;

typedef graph_node* pnode;
typedef graph_node* vertex_list;
typedef graph_node** adjacency_list;

list dfs_visit(pnode u)
{
    list l;
    int n = sizeof(u->adj) / sizeof(graph_node*);
    for (int i = 0; i < n; ++i)
    {
        if (u->adj[i]->c == white)
        {
            list_append(&l, (void*)generate_edge(u->index, u->adj[i]->index));
            // 在真实的项目里，千万千万千万不要这样写……一解引用就崩溃……
            // Never write code like this in a real-life program... 
            // Crash immediately when dereferencing...
            list temp = dfs_visit(u->adj[i]);
            l.tail->next = temp.head;
            temp.head->prev = l.tail;
            list_append(&l, (void*)generate_edge(u->adj[i]->index, u->index));
            // 还有这里也是……
            // And here too...
        }
    }
    return l;
}

vertex_list build_graph()
{
    vertex_list vl = calloc(9, sizeof(graph_node));

    vl[0].index = 0;
    vl[0].adj = calloc(2, sizeof(graph_node*));
    vl[0].adj[0] = vl + 1;
    vl[0].adj[1] = vl + 7;

    vl[1].index = 1;
    vl[1].adj = calloc(3, sizeof(graph_node*));
    vl[1].adj[0] = vl;
    vl[1].adj[1] = vl + 2;
    vl[1].adj[2] = vl + 7;

    vl[2].index = 2;
    vl[2].adj = calloc(4, sizeof(graph_node*));
    vl[2].adj[0] = vl + 1;
    vl[2].adj[1] = vl + 3;
    vl[2].adj[2] = vl + 5;
    vl[2].adj[3] = vl + 8;

    vl[3].index = 3;
    vl[3].adj = calloc(3, sizeof(graph_node*));
    vl[3].adj[0] = vl + 2;
    vl[3].adj[1] = vl + 4;
    vl[3].adj[2] = vl + 5;

    vl[4].index = 4;
    vl[4].adj = calloc(2, sizeof(graph_node*));
    vl[4].adj[0] = vl + 3;
    vl[4].adj[1] = vl + 5;

    vl[5].index = 5;
    vl[5].adj = calloc(4, sizeof(graph_node*));
    vl[5].adj[0] = vl + 2;
    vl[5].adj[1] = vl + 3;
    vl[5].adj[2] = vl + 4;
    vl[5].adj[3] = vl + 6;

    vl[6].index = 6;
    vl[6].adj = calloc(3, sizeof(graph_node*));
    vl[6].adj[0] = vl + 5;
    vl[6].adj[1] = vl + 7;
    vl[6].adj[2] = vl + 8;

    vl[7].index = 7;
    vl[7].adj = calloc(4, sizeof(graph_node*));
    vl[7].adj[0] = vl;
    vl[7].adj[1] = vl + 1;
    vl[7].adj[2] = vl + 6;
    vl[7].adj[3] = vl + 8;

    vl[8].index = 8;
    vl[8].adj = calloc(3, sizeof(graph_node*));
    vl[8].adj[0] = vl + 2;
    vl[8].adj[1] = vl + 6;
    vl[8].adj[2] = vl + 7;

    return vl;
}

void free_vertex_list(vertex_list vl)
{
    int n = sizeof(vl) / sizeof(graph_node);
    for (int i = 0; i < n; ++i)
        free(vl[i].adj);
    free(vl);
}

void print_solution(list* l)
{
    list_node* current = l->head;
    while (current)
    {
        printf("%2d->%2d ", ((unsigned)current->content) >> 16, ((unsigned)current->content) & 0xffff);
        current = current->next;
    }
}

int main(void)
{
    vertex_list vl = build_graph();
    list l = dfs_visit(vl);
    print_solution(&l);
    list_free(&l);
    return 0;
}