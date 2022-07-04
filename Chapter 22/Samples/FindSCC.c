#include <stdlib.h>
#include <stdio.h>
#include "..\List\List.h"

#define get_index(x)    (((graph_node*)((x)->content))->index)
#define get_f(x)        (((graph_node*)((x)->content))->f)

typedef enum color
{
    white,
    black
} color;

typedef struct graph_node
{
    int f;
    int index;
    color c;
    list adj;
} graph_node;

typedef graph_node* vertex_list;
typedef graph_node* pnode;

void delete_graph(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
        list_free(&(vl[i].adj));
    free(vl);
}

void transpose(vertex_list* vl, int n)
{
    vertex_list new_graph = calloc(n, sizeof(graph_node));

    for (int i = 0; i < n; ++i)
    {
        pnode u = *vl + i;
        new_graph[i].f = u->f;
        new_graph[i].index = u->index;
        list_node* current = u->adj.head;
        while (current)
        {
            pnode v = new_graph + get_index(current);
            list_append(&v->adj, new_graph + i);
            current = current->next;
        }
    }

    delete_graph(*vl, n);
    *vl = new_graph;
}

static int time = 0;

void dfs_visit(pnode u)
{
    list_node* current = u->adj.head;
    u->c = black;

    while (current)
    {
        pnode v = current->content;
        if (v->c == white)
            dfs_visit(v);
        current = current->next;
    }
    u->f = time++;
}

void dfs(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
        if (vl[i].c == white)
            dfs_visit(vl + i);
}

list sort(vertex_list vl, int n)
{
    list l = { NULL, NULL };
    list_append(&l, vl);

    for (int i = 1; i < n; ++i)
    {
        list_node* current = l.head;
        while (current)
        {
            if (vl[i].f < get_f(current))
                current = current->next;
            else
            {
                list_node* new_node = calloc(1, sizeof(graph_node));
                new_node->content = vl + i;
                current->prev->next = new_node;
                new_node->prev = current->prev;
                current->prev = new_node;
                new_node->next = current;
                break;
            }
        }
        if (!current)
            list_append(&l, vl + i);
    }

    return l;
}

void dfs_visit_print(pnode u)
{
    printf("%d ", u->index);
    u->c = black;

    list_node* current = u->adj.head;
    while (current)
    {
        pnode v = current->content;
        if (v->c == white)
            dfs_visit_print(v);

        current = current->next;
    }
    u->f = time++;
}

void dfs_f_descending(vertex_list vl, int n)
{
    list l = sort(vl, n);
    list_node* current = l.head;

    for (int i = 0; i < n; ++i)
        vl[i].c = white;
    time = 0;

    while (current)
    {
        pnode u = current->content;
        if (u->c == white)
        {
            dfs_visit_print(u);
            printf("\n");
        }
        current = current->next;
    }
}

vertex_list build_graph()
{
    vertex_list vl = calloc(8, sizeof(graph_node));

    vl[0].index = 0;
    list_append(&(vl[0].adj), vl + 1);

    vl[1].index = 1;
    list_append(&(vl[1].adj), vl + 2);
    list_append(&(vl[1].adj), vl + 4);
    list_append(&(vl[1].adj), vl + 5);

    vl[2].index = 2;
    list_append(&(vl[2].adj), vl + 3);
    list_append(&(vl[2].adj), vl + 6);

    vl[3].index = 3;
    list_append(&(vl[3].adj), vl + 2);
    list_append(&(vl[3].adj), vl + 7);

    vl[4].index = 4;
    list_append(&(vl[4].adj), vl);
    list_append(&(vl[4].adj), vl + 5);

    vl[5].index = 5;
    list_append(&(vl[5].adj), vl + 6);

    vl[6].index = 6;
    list_append(&(vl[6].adj), vl + 5);
    list_append(&(vl[6].adj), vl + 7);

    vl[7].index = 7;
    list_append(&(vl[7].adj), vl + 7);

    return vl;
}

int main(void)
{
    vertex_list vl = build_graph();
    dfs(vl, 8);
    transpose(&vl, 8);
    dfs_f_descending(vl, 8);
    delete_graph(vl, 8);
    return 0;
}