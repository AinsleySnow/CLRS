#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue\Queue.h"

typedef enum color
{
    white,
    black
} color;

typedef enum category
{
    babyfaces,
    heels
} category;

typedef struct wrestler
{
    int index;
    int d;
    color cr;
    category cy;
    int adj_len;
    struct wrestler** adj;
} wrestler;

typedef wrestler* vertex_list;
typedef wrestler* pwrestler;
typedef wrestler** adjacency_list;

void mark_category(vertex_list vl, int n)
{
    queue q = { NULL, NULL };
    enqueue(&q, vl);
    vl[0].cr = black;
    vl[0].d = 0;

    while (!is_empty(&q))
    {
        pwrestler pw = dequeue(&q);
        int adj_len = pw->adj_len;

        for (int i = 0; i < adj_len; ++i)
        {
            pwrestler v = pw->adj[i];
            if (v->cr == white)
            {
                enqueue(&q, v);
                v->d = pw->d + 1;
            }
        }
        pw->cr = black;
    }

    for (int i = 0; i < n; ++i)
    {
        if (vl[i].d % 2 == 0)
            vl[i].cy = babyfaces;
        else
            vl[i].cy = heels;
    }
}

bool check(vertex_list vl, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int adj_len = vl[i].adj_len;
        for (int j = 0; j < adj_len; ++j)
            if ((vl[i].adj[j])->cy == vl[i].cy)
                return false;
    }

    return true;
}

vertex_list build_graph1()
{
    vertex_list vl = calloc(8, sizeof(wrestler));

    vl[0].adj = calloc(2, sizeof(pwrestler));
    vl[0].adj_len = 2;
    vl[0].adj[0] = vl + 1;
    vl[0].adj[1] = vl + 3;

    vl[1].adj = calloc(3, sizeof(pwrestler));
    vl[1].adj_len = 3;
    vl[1].adj[0] = vl;
    vl[1].adj[1] = vl + 2;
    vl[1].adj[2] = vl + 3;

    vl[2].adj = calloc(3, sizeof(pwrestler));
    vl[2].adj_len = 3;
    vl[2].adj[0] = vl + 1;
    vl[2].adj[1] = vl + 4;
    vl[2].adj[2] = vl + 5;

    vl[3].adj = calloc(3, sizeof(pwrestler));
    vl[3].adj_len = 3;
    vl[3].adj[0] = vl;
    vl[3].adj[1] = vl + 1;
    vl[3].adj[2] = vl + 4;

    vl[4].adj = calloc(3, sizeof(pwrestler));
    vl[4].adj_len = 3;
    vl[4].adj[0] = vl + 2;
    vl[4].adj[1] = vl + 3;
    vl[4].adj[2] = vl + 5;

    vl[5].adj = calloc(4, sizeof(pwrestler));
    vl[5].adj_len = 4;
    vl[5].adj[0] = vl + 2;
    vl[5].adj[1] = vl + 4;
    vl[5].adj[2] = vl + 6;
    vl[5].adj[3] = vl + 7;

    vl[6].adj = calloc(1, sizeof(pwrestler));
    vl[6].adj_len = 1;
    vl[6].adj[0] = vl + 5;

    vl[7].adj = calloc(1, sizeof(pwrestler));
    vl[7].adj_len = 1;
    vl[7].adj[0] = vl + 5;

    return vl;
}

vertex_list build_graph2()
{
    vertex_list vl = calloc(4, sizeof(wrestler));

    vl[0].adj = calloc(2, sizeof(pwrestler));
    vl[0].adj_len = 2;
    vl[0].adj[0] = vl + 1;
    vl[0].adj[1] = vl + 2;

    vl[1].adj = calloc(2, sizeof(pwrestler));
    vl[1].adj_len = 2;
    vl[1].adj[0] = vl;
    vl[1].adj[1] = vl + 3;

    vl[2].adj = calloc(2, sizeof(pwrestler));
    vl[2].adj_len = 2;
    vl[2].adj[0] = vl;
    vl[2].adj[1] = vl + 3;

    vl[3].adj = calloc(2, sizeof(pwrestler));
    vl[3].adj_len = 2;
    vl[3].adj[0] = vl + 1;
    vl[3].adj[1] = vl + 2;

    return vl;
}

int main(void)
{
    vertex_list g1 = build_graph1();
    mark_category(g1, 8);
    printf("%d\n", check(g1, 8));

    vertex_list g2 = build_graph2();
    mark_category(g2, 4);
    printf("%d\n", check(g2, 4));

    for (int i = 0; i < 8; ++i)
        free(g1[i].adj);
    free(g1);
    for (int i = 0; i < 4; ++i)
        free(g2[i].adj);
    free(g2);

    return 0;
}