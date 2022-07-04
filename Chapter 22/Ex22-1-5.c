#include "List\List.h"
#include <stdio.h>
#include <stdlib.h>

#define get_content(x)      ((graph_node*)((x)->content))
#define mark_color(x, y)    (x) |= ((y) << 30)
#define get_color(x)        (((x) >> 30) & 0b11)
#define is_connected(x)      ((x) & 1)
#define mark_pi(x, y)       (x) |= (((y) & 0x1fffffff) << 1)
#define get_pi(x)           (((x) >> 1) & 0x1fffffff)

typedef enum color
{
    white = 1,
    gray,
    black
} color;

typedef list* adjacency_list;

typedef struct graph_node
{
    color c;
    int index;
    struct graph_node* pi;
    adjacency_list adj;
} graph_node;

typedef graph_node* pnode;
typedef graph_node* vertex_list;

vertex_list find_g_square_list(vertex_list g, int n)
{
    vertex_list g_square = calloc(n, sizeof(graph_node));
    for (int i = 0; i < n; ++i)
    {
        g_square[i].index = i;
        g_square[i].adj = calloc(1, sizeof(list));
    }

    for (int i = 0; i < n; ++i)
    {
        if (g[i].c == white)
        {
            g[i].c = black;
            list_node* current = g[i].adj->head;
            while (current)
            {
                get_content(current)->c = gray;
                get_content(current)->pi = g + i;
                list_append(g_square[i].adj, g_square + get_content(current)->index);
                current = current->next;
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        if (g[i].c == gray)
        {
            list_node* current = g[i].adj->head;
            while (current)
            {
                list_append(g_square[i].adj, g_square + get_content(current)->index);
                list_append((g_square + (g[i].pi - g))->adj, g_square + get_content(current)->index);
                current = current->next;
            }
        }
    }

    return g_square;
}

vertex_list bulid_list()
{
    vertex_list vl = calloc(6, sizeof(graph_node));
    for (int i = 0; i < 6; ++i)
    {
        vl[i].index = i;
        vl[i].c = white;
        vl[i].adj = calloc(1, sizeof(list));
    }

    list_append(vl[0].adj, vl + 1);
    list_append(vl[0].adj, vl + 3);

    list_append(vl[1].adj, vl + 4);

    list_append(vl[2].adj, vl + 4);
    list_append(vl[2].adj, vl + 5);

    list_append(vl[3].adj, vl + 2);

    list_append(vl[5].adj, vl + 3);

    list_append(vl[5].adj, vl + 5);

    return vl;
}

void print_graph(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("index = %d\nadjacency list = ", vl[i].index);
        list_node* current = vl[i].adj->head;
        while (current)
        {
            printf("%d ", ((graph_node*)current->content)->index);
            current = current->next;
        }
        printf("\n");
    }
}

int** find_g_square_matrix(int** g, int n)
{
    int** g_square = calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i)
        g_square[i] = calloc(n, sizeof(int));

    // 0: white 1: black 2: gray
    for (int i = 0; i < n; ++i)
    {
        if (!get_color(g[i][0]))
        {
            mark_color(g[i][0], 1);
            for (int j = 0; j < n; ++j)
            {
                if (is_connected(g[i][j]))
                {
                    mark_color(g[j][0], 2);
                    mark_pi(g[j][0], i);
                    g_square[i][j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        if (get_color(g[i][0]) == 2)
        {
            int pi = get_pi(g[i][0]);
            for (int j = 0; j < n; ++j)
            {
                if (is_connected(g[i][j]))
                {
                    g_square[i][j] = 1;
                    g_square[pi][j] = 1;
                }                    
            }
        }
    }

    return g_square;
}

int** bulid_matrix()
{
    int** matrix = calloc(6, sizeof(int*));
    for (int i = 0; i < 6; ++i)
        matrix[i] = calloc(6, sizeof(int));

    matrix[0][1] = 1;
    matrix[0][3] = 1;

    matrix[1][4] = 1;
    
    matrix[2][4] = 1;
    matrix[2][5] = 1;

    matrix[3][2] = 1;

    matrix[5][3] = 1;
    matrix[5][5] = 1;

    return matrix;
}

int main(void)
{
    vertex_list vl = bulid_list();
    vertex_list vl_square = find_g_square_list(vl, 6);
    print_graph(vl_square, 6);

    for (int i = 0; i < 6; ++i)
    {
        list_free(vl[i].adj);
        list_free(vl_square[i].adj);
    }
    free(vl);
    free(vl_square);


    printf("\n\n");


    int** matrix = bulid_matrix();
    int** matrix_square = find_g_square_matrix(matrix, 6);
    
    printf(" \\ | ");
    for (int i = 0; i < 6; ++i)
        printf("%d ", i);
    printf("\n---+-------------\n");
    for (int i = 0; i < 6; ++i)
    {
        printf(" %d | ", i);
        for (int j = 0; j < 6; ++j)
            printf("%d ", matrix_square[i][j]);
        printf("\n");
    }

    for (int i = 0; i < 6; ++i)
    {
        free(matrix[i]);
        free(matrix_square[i]);
    }
    free(matrix);
    free(matrix_square);

    return 0;
}