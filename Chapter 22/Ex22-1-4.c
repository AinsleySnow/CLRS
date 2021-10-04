#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph_node
{
    int index;
    adjacency_list adj;
} graph_node;

typedef struct list_node
{
    void* content;
    struct list_node* next;
} list_node;

typedef list_node* adjacency_list;
typedef graph_node* vertex_list;

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

void node_remove(adjacency_list adj, void* content)
{
    list_node* head = adj;
    list_node* trailing = NULL;
    while (head)
    {
        trailing = head;
        if (head->content == content)
        {
            trailing->next = head->next;
            free(head);
            return;
        }
    }
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

vertex_list get_g_prime(vertex_list original)
{
    int n = sizeof(original) / sizeof(graph_node);

    for (int i = 0; i < n; ++i)
    {
        list_node* head = original[i].adj;
        while (head)
        {
            if (head->content != original + i)
            {
                adjacency_list to_be_looked_up = ((graph_node*)head->content)->adj;
                if (!is_in(to_be_looked_up, original + i))
                    append(to_be_looked_up, original + i);
            }
            else
                node_remove(head, original + i);
        }
    }
}

vertex_list build_graph()
{
    vertex_list vl = calloc(6, sizeof(graph_node));

    vl[0].index = 1;
    append(vl[0].adj, vl + 1);
    append(vl[0].adj, vl + 3);

    vl[1].index = 2;
    append(vl[1].adj, vl + 4);

    vl[2].index = 3;
    append(vl[2].adj, vl + 4);
    append(vl[2].adj, vl + 5);

    vl[3].index = 4;
    append(vl[3].adj, vl + 2);

    vl[4].index = 5;
    append(vl[5].adj, vl + 3);

    vl[5].index = 6;
    append(vl[5].adj, vl + 5);

    return vl;
}

void print_graph(vertex_list vl)
{
    int n = sizeof(vl) / sizeof(graph_node);
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
    get_g_prime(g);
    print_graph(g);

    return 0;
}