#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list_node
{
    void* content;
    struct list_node* next;
} list_node;

typedef list_node* adjacency_list;

typedef struct graph_node
{
    int index;
    adjacency_list adj;
} graph_node;

typedef graph_node* vertex_list;


void append(adjacency_list* adj, void* content)
{
    list_node* new_node = calloc(1, sizeof(list_node));
    new_node->content = content;
    
    if (*adj)
    {
        list_node* next = *adj;
        *adj = new_node;
        (*adj)->next = next;
    }
    else
        *adj = new_node;
}

bool is_in(adjacency_list adj, void* content)
{
    list_node* head = adj;
    while (head)
    {
        if (head->content == content)
            return true;
        head = head->next;
    }

    return false;
}

vertex_list get_g_prime(vertex_list original, int n)
{
    vertex_list new_graph = calloc(n, sizeof(graph_node));

    for (int i = 0; i < n; ++i)
    {
        new_graph[i].index = original[i].index;
        for (list_node* v = original[i].adj; v; v = v->next)
        {
            if (((graph_node*)v->content)->index == i)
                continue;
            else if (!is_in(new_graph[i].adj, new_graph + ((graph_node*)v->content)->index))
            {
                append(&new_graph[i].adj, new_graph + ((graph_node*)v->content)->index);
                append(&((new_graph + ((graph_node*)v->content)->index)->adj), new_graph + i);
            }
        }
    }

    return new_graph;
}

vertex_list build_graph()
{
    vertex_list vl = calloc(6, sizeof(graph_node));

    vl[0].index = 0;
    append(&vl[0].adj, vl + 1);
    append(&vl[0].adj, vl + 3);

    vl[1].index = 1;
    append(&vl[1].adj, vl + 4);

    vl[2].index = 2;
    append(&vl[2].adj, vl + 4);
    append(&vl[2].adj, vl + 5);

    vl[3].index = 3;
    append(&vl[3].adj, vl + 2);
    append(&vl[3].adj, vl);
    append(&vl[3].adj, vl);

    vl[4].index = 4;
    append(&vl[4].adj, vl + 3);

    vl[5].index = 5;
    append(&vl[5].adj, vl + 5);

    return vl;
}

void print_graph(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("index = %d\nadjacency list = ", vl[i].index);
        list_node* head = vl[i].adj;
        while (head)
        {
            printf("%d ", ((graph_node*)head->content)->index);
            head = head->next;
        }
        printf("\n");
    }
}

int main(void)
{
    vertex_list g = build_graph();
    vertex_list new_graph = get_g_prime(g, 6);
    print_graph(new_graph, 6);

    return 0;
}