#include <stdio.h>
#include <stdlib.h>
#include "Queue\Queue.h"

typedef enum color
{
    white,
    gray,
    black
} color;

typedef struct graph_vertex
{
    int d;
    int pi;
    int isConnected;
    color c;
} graph_vertex;

void bfs_matrix(graph_vertex** g, int s, int n)
{
    queue q = { NULL, NULL };

    g[s][0].d = 0;

    enqueue(&q, (void*)s);
    while (!is_empty(&q))
    {
        int i = (int)dequeue(&q);

        g[i][0].c = black;
        for (int j = 0; j < n; ++j)
        {
            if (g[i][j].isConnected)
            {
                if (g[j][0].c == white)
                {
                    g[j][0].pi = i;
                    g[j][0].c = gray;
                    g[j][0].d = g[i][0].d + 1;
                    enqueue(&q, (void*)j);
                }
            }
        }
    }
}

int main(void)
{
    graph_vertex** g = calloc(8, sizeof(graph_vertex*));
    for (int i = 0; i < 8; ++i)
    {
        g[i] = calloc(8, sizeof(graph_vertex));
        g[i][0].pi = -1;
    }
    
    g[0][1].isConnected = 1;
    g[0][4].isConnected = 1;

    g[1][0].isConnected = 1;
    g[1][5].isConnected = 1;

    g[2][3].isConnected = 1;
    g[2][5].isConnected = 1;
    g[2][6].isConnected = 1;

    g[3][2].isConnected = 1;
    g[3][6].isConnected = 1;
    g[3][7].isConnected = 1;

    g[4][0].isConnected = 1;

    g[5][1].isConnected = 1;
    g[5][2].isConnected = 1;
    g[5][6].isConnected = 1;

    g[6][2].isConnected = 1;
    g[6][3].isConnected = 1;
    g[6][5].isConnected = 1;
    g[6][7].isConnected = 1;

    g[7][3].isConnected = 1;
    g[7][6].isConnected = 1;

    bfs_matrix(g, 1, 8);

    for (int i = 0; i < 8; ++i)
    {
        printf("index = %2d, pi = %2d, d = %2d", i, g[i][0].pi, g[i][0].d);
        printf("\n");
    }

    return 0;
}