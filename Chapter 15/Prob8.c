#include <stdio.h>
#include <stdlib.h>

#undef min
#define LEFT    0
#define UP      1
#define RIGHT   2

void find_table(int** bp, int x, int y, int*** dis_table, char*** dire)
{
    int** disruption_table = calloc(x + 1, sizeof(int*));
    for (int i = 0; i <= x; ++i)
        disruption_table[i] = calloc(y + 1, sizeof(int));
    for (int i = 0; i <= y; ++i)
        disruption_table[0][i] = 0x7fffffff;
    for (int i = 1; i <= x; ++i)
        disruption_table[i][0] = 0x7fffffff;

    char** direction = calloc(x, sizeof(char*));
    for (int i = 0; i < x; ++i)
        direction[i] = calloc(y, sizeof(char));

    for (int i = 1; i <= x; ++i)
    {
        for (int j = 1; j <= y; ++j)
        {
            int x = disruption_table[i - 1][j - 1],
                y = disruption_table[i - 1][j],
                z = disruption_table[i - 1][j + 1];
            int xy = x > y ? y : x;
            char dxy = x > y ? UP : LEFT;
            int xz = x > z ? z : x;
            char dxz = x > z ? RIGHT : LEFT;
            int min = xy > xz ? xz : xy;
            char d = xy > xz ? dxz : dxy;

            disruption_table[i][j] = bp[i - 1][j - 1] + min;
            direction[i - 1][j - 1] = d;
        }
    }

    *dis_table = disruption_table;
    *dire = direction;
}

void build_solution(int x, int y, int** disruption_table, int** direction)
{
    int min = 0x7fffffff, pos = 0;
    for (int i = 1; i <= y; ++i)
    {
        if (disruption_table[x][i] < min)
        {
            min = disruption_table[x][i];
            pos = i;
        }
    }

    int row = x;
    while (row >= 1)
    {
        disruption_table[row][pos] = -1;

        if (direction[row - 1][pos - 1] == LEFT)
            pos--;
        else if (direction[row - 1][pos - 1] == RIGHT)
            pos++;
        --row;
    }

    for (int i = 1; i <= x; ++i)
    {
        for (int j = 1; j <= y; ++j)
            if (disruption_table[i][j] > 0)
                printf("%4d", disruption_table[i][j]);
        printf("\n");
    }
}

int main()
{
    int bitmap[][3] = {
        { 4, 5, 6 },
        { 3, 2, 8 },
        { 6, 1, 3 }
    };

    int** disruption_table = NULL;
    int** direction = NULL;
    find_table(bitmap, 3, 3, &disruption_table, &direction);
    build_solution(3, 3, disruption_table, direction);

    for (int i = 0; i < 4; ++i)
        free(disruption_table[i]);
    free(disruption_table);
    for (int i = 0; i < 3; ++i)
        free(direction[i]);
    free(direction);

    return 0;
}