#include <stdlib.h>
#include <stdio.h>
#include "List\List.h"

#define get_index(x)    (((graph_node*)((x)->content))->index)
#define get_f(x)        (((graph_node*)((x)->content))->f)
#define get_scc(x)      (((graph_node*)((x)->content))->scc)

typedef enum color
{
    white,
    black
} color;

typedef struct graph_node
{
    int f;
    int index;
    int scc;
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

void dfs_visit_scc(pnode u, int scc)
{
    u->c = black;
    u->scc = scc;

    list_node* current = u->adj.head;
    while (current)
    {
        pnode v = current->content;
        if (v->c == white)
            dfs_visit_scc(v, scc);

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

    int scc = 0;
    while (current)
    {
        pnode u = current->content;
        if (u->c == white)
            dfs_visit_scc(u, scc);
        current = current->next;
        scc += 1;
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

void drop(list_node* node, list* l)
{
    if (node->next)
        node->next->prev = node->prev;
    if (node->prev)
        node->prev->next = node->next;
    if (l->head == node)
        l->head = node->next;
    if (l->tail == node)
        l->tail = node->prev;

    free(node);
}

void print_graph(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d: ", vl[i].index);
        for (list_node* node = vl[i].adj.head; node; node = node->next)
            printf("%d ", get_index(node));
        printf("\n");
    }
}

int main(void)
{
    vertex_list vl = build_graph();
    print_graph(vl, 8);

    dfs(vl, 8);
    transpose(&vl, 8);
    dfs_f_descending(vl, 8);

    int is_connected[][8] = {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    for (int i = 0; i < 8; ++i)
    {
        for (list_node* node = vl[i].adj.head; node;)
        {
            if (vl[i].scc != get_scc(node) && is_connected[vl[i].scc][get_scc(node)])
            {
                list_node* temp = node;
                node = node->next;
                drop(temp, &vl[i].adj);
            }
            else if (vl[i].scc != get_scc(node))
            {
                is_connected[vl[i].scc][get_scc(node)] = 1;
                node = node->next;
            }
            else
                node = node->next;
        }
    }

    transpose(&vl, 8);
    printf("\n");
    print_graph(vl, 8);
    delete_graph(vl, 8);
    return 0;
}