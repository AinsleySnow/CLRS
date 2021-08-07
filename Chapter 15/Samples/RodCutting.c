#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#undef max

int max(int a, int b)
{
    return a > b ? a : b;
}

int rod_cut(int* prices, int len)
{
    if (len == 0)
        return 0;
    int ans = INT_MIN;
    for (int i = 1; i <= len; ++i)
        ans = max(ans, prices[i - 1] + rod_cut(prices, len - i));
    return ans;
}

int memoized_cut_rod_aux(int* prices, int len, int* saved)
{
    if (saved[len] >= 0)
        return saved[len];

    int ans = 0;
    if (len)
    {
        for (int i = 1; i <= len; ++i)
            ans = max(ans, prices[i - 1] + memoized_cut_rod_aux(prices, len - i, saved));
        saved[len] = ans;
    }
    return ans;
}

int memoized_cut_rod(int* prices, int n)
{
    int* saved = malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= n; ++i)
        saved[i] = INT_MIN;
    saved[0] = 0;

    int ans = memoized_cut_rod_aux(prices, n, saved);
    
    free(saved);
    return ans;
}

int bottom_up_cut_rod(int* prices, int len)
{
    int* saved = malloc(sizeof(int) * (len + 1));
    saved[0] = 0;
    
    int ans = INT_MIN;
    for (int j = 1; j <= len; ++j)
    {
        ans = INT_MIN;
        for (int i = 1; i <= j; ++i)
            ans = max(ans, prices[i - 1] + saved[j - i]);
        saved[j] = ans;
    }

    free(saved);
    return ans;    
}

void extended_bottom_up_cut_rod(int* prices, int len, int** saved, int** split)
{
    if (*saved)
        free(*saved);
    if (*split)
        free(*split);
    *saved = malloc(sizeof(int) * (len + 1));
    *split = malloc(sizeof(int) * (len + 1));
    (*saved)[0] = 0;

    int ans = INT_MIN;
    for (int j = 1; j <= len; ++j)
    {
        ans = INT_MIN;
        for (int i = 1; i <= j; ++i)
        {
            if (ans < prices[i - 1] + (*saved)[j - i])
            {
                ans = prices[i - 1] + (*saved)[j - i];
                (*split)[j] = i;
            }
        }
        (*saved)[j] = ans;
    }
}

void print_cut_rod_solution(int n, const int* saved)
{
    printf("%d = ", n);
    while (n > 0)
    {
        printf("+ %2d ", saved[n]);
        n -= saved[n];
    }
}

int main(void)
{
    int prices[10] = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
    printf("rod_cut returns %d.\n", rod_cut(prices, 10));
    printf("memoized_cut_rod returns %d.\n", memoized_cut_rod(prices, 10));
    printf("bottom_up_cut_rod returns %d.\n", bottom_up_cut_rod(prices, 10));

    int* saved = NULL;
    int* split = NULL;
    extended_bottom_up_cut_rod(prices, 10, &saved, &split);
    print_cut_rod_solution(10, split);

    return 0;
}