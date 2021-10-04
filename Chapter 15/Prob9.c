#include <stdio.h>
#include <stdlib.h>

#undef min

void break_string(int* words, int n, int*** seq, int*** cos)
{
    int** cost = calloc(n + 1, sizeof(int*));
    for (int i = 0; i <= n; ++i)
        cost[i] = calloc(n + 1, sizeof(int));

    int** seperate = calloc(n + 1, sizeof(int*));
    for (int i = 0; i <= n; ++i)
        seperate[i] = calloc(n + 1, sizeof(int));

    for (int i = 0; i <= n; ++i)
        cost[i][i] = words[i];
    for (int len = 1; len <= n; ++len)
    {
        for (int i = 1; i <= n - len + 1; ++i)
        {
            int j = i + len - 1, min = 0x7fffffff;
            for (int k = i; k < j; ++k)
            {
                int temp = cost[i][k] + cost[k + 1][j - 1] + words[j];
                if (min > temp)
                {
                    min = temp;
                    seperate[i][j] = k;
                }
            }
            cost[i][j] = min;
        }
    }

    *cos = cost;
    *seq = seperate;
}

void print_solution(int* words, int** sequence, int start, int end)
{
    if (start <= end)
    {
        int seperator = sequence[start][end];
        for (int i = start; i <= seperator; ++i)
            printf("%d ", words[i]);
        printf("\n");
        for (int i = seperator + 1; i <= end; ++i)
            printf("%d ", words[i]);
        printf("\n");

        print_solution(words, sequence, start, seperator);
        print_solution(words, sequence, seperator + 1, end);
    }
}

int main()
{
    int words[] = { 0, 2, 6, 2, 10 };
    int** sequence = NULL;
    int** cost = NULL;

    break_string(words, 4, &sequence, &cost);
    printf("cost = %d\n", cost[1][4]);
    print_solution(words, sequence, 1, 4);

    for (int i = 0; i <= 4; ++i)
        free(sequence[i]);
    free(sequence);
    for (int i = 0; i <= 4; ++i)
        free(cost[i]);
    free(cost);

    return 0;
}