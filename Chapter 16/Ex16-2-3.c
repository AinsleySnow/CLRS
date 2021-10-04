#include <stdio.h>
#include <stdlib.h>

#undef max
#define max(x, y) (((x) > (y)) ? (x) : (y))

void build_solution(const int* worth, const int* weight, int capacity, int*** t)
{
    int n = sizeof(worth) / sizeof(int);
    int** table = calloc(capacity + 1, sizeof(int*));
    for (int i = 0; i <= capacity; ++i)
        table[i] = calloc(n + 1, sizeof(int));
    
    for (int i = 0; i < capacity; ++i)
        for (int j = 0; j < n; ++j)
            if (i >= weight[j])
                table[i][j] = max(table[i - weight[j]] + worth[j], table[i - weight[j]]);

    *t = table;
}

void print_solution(const int** table, int* weight, int capacity, int n)
{
    int i = capacity, j = n;
    while (i > 0)
    {
        if (table[i - weight[j]][j] == table[i][j])
            --j;
        else
        {
            printf("%d ", j);
            i -= weight[j];
            --j;
        }
    }
}

int main(void)
{
    int weight[] = { 10, 20, 30 };
    int worth[] = { 60, 100, 120 };
    int capacity = 50;
    int** output = NULL;

    build_solution(worth, weight, capacity, output);
    print_solution(output, weight, capacity, 3);

    for (int i = 0; i < capacity; ++i)
        free(output[i]);
    free(output);
    return 0;
}