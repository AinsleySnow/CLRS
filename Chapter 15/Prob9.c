#include <stdio.h>
#include <stdlib.h>

#undef min

void break_string(int* words, int n, const int*** seq, const int*** cos)
{
    int** cost = calloc(n + 1, sizeof(int*));
    for (int i = 0; i <= n; ++i)
        cost[i] = calloc(n + 1, sizeof(int));

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
                    min = temp;
            }
            cost[i][j] = min;
        }
    }

    *cos = cost;
}

int main()
{
    return 0;
}