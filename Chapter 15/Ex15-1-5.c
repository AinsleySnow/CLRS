#include <stdlib.h>
#include <stdio.h>

unsigned long long fibo(int n)
{
    if (n == 0)
        return 0;

    unsigned long long n1 = 1, n2 = 1, ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ans = n1 + n2;
        n1 = n2;
        n2 = ans;
    }
    return ans;
}

int main(void)
{
    printf("%lld", fibo(4));
    return 0;
}