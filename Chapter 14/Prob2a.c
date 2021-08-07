//Problem 14-2 Josephus permutation a.
#include <stdio.h>

int main(void)
{
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);
    int list[n];

    for(int i = 0; i < n; ++i)
        list[i] = 1;

    int sum = 0, poped = 0;
    for (int i = 0; poped != n;)
    {
        sum += list[i];
        if(sum == m)
        {
            list[i] = 0;
            printf("%d ", i + 1);
            poped++;
            sum = 0;
        }

        ++i;
        if(i == n)
            i %= n;
    }

    return 0;
}