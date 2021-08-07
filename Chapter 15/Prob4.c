#include <stdio.h>
#include <stdlib.h>
#undef min

int brute_force(int* words, int m, int start, int end);

int printing_neatly(int* words, int n, int m)
{
    int** saved = calloc(n + 1, sizeof(int*));
    for (int i = 0; i < n; ++i)
        saved[i] = calloc(n, sizeof(int));

    for (int len = 1; len <= n; ++len)
    {
        for (int i = 0; i < n - len + 1; ++i)
        {
            int j = i + len - 1;
            saved[i][i] = m - words[i];
            for (int k = i + 1; k <= j; ++k)
                saved[i][k] = saved[i][k - 1] - (1 + words[k]);
        }
    }

    int* cost = calloc(n, sizeof(int));

    cost[0] = saved[0][0];
    for (int j = 1; j < n; ++j)
    {
        int min = 0x7fffffff;
        for (int i = 0; i <= j; ++i)
        {
            if (saved[i][j] < 0)
                continue;
            int temp = (i - 1 < 0 ? 0 : cost[i - 1]) + saved[i][j];
            if (min > temp)
                min = temp;
        }
        cost[j] = min;
    }

    int ans = cost[n - 1];

    free(cost);
    for (int i = 0; i < n; ++i)
        free(saved[i]);
    free(saved);

    return ans;
}

int main(void)
{
    int words[] = { 3,3,6,11,3,3,2,9,3,7,4,
                   14,4,5,3,5,4,3,4,4,3,2,
                   3,2,4,4,2,3,3,4,2,3,4,4,
                   5,4,2,5,7,8,4,7,2,2,2,3,
                   2,3,2,7,2,4,2,3,2,4,5,7,
                   2,4,1,5,9,1,9,4,5,10,9,
                   9,8,5,10,3,10,6,9,7,5,
                   5,3,6,2,4,2,5,7,8,5,3,5,
                   9,8,4,4,7,4,7,7,2,1 };

    printf("%d ", printing_neatly(words, 101, 80));
    //printf("%d", brute_force(words, 80, 0, 100));
    return 0;
}

int brute_force(int* words, int m, int start, int end)
{
    if (start <= end)
    {
        int min = 0x7fffffff;
        for (int i = start; i <= end; ++i)
        {
            int sum = 0;
            for (int j = start; j <= i; ++j)
                sum -= words[j];
            sum += m - i + start;
            if (sum < 0)
                continue;

            int ans = brute_force(words, m, i + 1, end);
            if (ans < 0)
                continue;
            ans += sum;

            if (min > ans)
                min = ans;
        }
        return min;
    }
    return 0;
}