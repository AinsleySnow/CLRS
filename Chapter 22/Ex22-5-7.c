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

vertex_list dfs_f_descending(vertex_list vl, int n, int* scc)
{
    list l = sort(vl, n);
    list_node* current = l.head;

    for (int i = 0; i < n; ++i)
        vl[i].c = white;
    time = 0;

    *scc = 0;
    while (current)
    {
        pnode u = current->content;
        if (u->c == white)
        {
            dfs_visit_scc(u, *scc);
            *scc += 1;
        }
        current = current->next;
    }

    vertex_list vscc = calloc(*scc, sizeof(graph_node));
    for (int i = 0; i < *scc; ++i)
        vscc[i].index = i;
    for (list_node* w = l.head; w; w = w->next)
    {
        pnode u = (pnode)w->content;
        for (list_node* v = u->adj.head; v; v = v->next)
            if (u->scc != get_scc(v))
                list_append(&vscc[u->scc].adj, vscc + get_scc(v));
    }

    list_free(&l);
    return vscc;
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

bool is_semiconnected(vertex_list vl, int n)
{  
    dfs(vl, n);
    list l = sort(vl, n);
    for (list_node* u = l.head; u->next; u = u->next)
    {
        pnode v = (pnode)u->content;
        pnode next = u->next->content;
        bool result = false;
        for (list_node* nv = v->adj.head; nv; nv = nv->next)
        {
            result |= get_index(nv) == next->index;
            if (get_index(nv) == next->index)
                break;
        }
        if (!result)
            return false;
    }

    return true;
}

int main(void)
{
    vertex_list vl = build_graph();

    dfs(vl, 8);
    transpose(&vl, 8);

    int nscc = 0;
    vertex_list vscc = dfs_f_descending(vl, 8, &nscc);
    transpose(&vscc, nscc);

    printf("The graph %s semiconnected.", is_semiconnected(vscc, nscc) ? "is" : "isn't");

    delete_graph(vl, 8);
    delete_graph(vscc, nscc);
    return 0;
}