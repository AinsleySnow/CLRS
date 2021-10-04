#include <stdlib.h>
#include <stdio.h>

int comp(const void* a, const void* b)
{
    float difference = *(float*)a - *(float*)b;
    return difference < 0 ? 1 : -1;
}

float fractional_knapsack(const int* price, const int* weight, int n, int capacity)
{
    float ans = 0;
    float* unit_price = calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i)
        unit_price[i] = (float)weight[i] / (float)price[i];
    qsort(unit_price, n, sizeof(float), comp);

    int i = 0;
    while (capacity)
    {
        if (capacity > weight[i])
        {
            capacity -= weight[i++];
            ans += weight[i] * unit_price[i];
        }
        else
        {
            ans += unit_price[i] * capacity;
            capacity = 0;
        }
    }

    free(unit_price);
    return ans;
}

int main(void)
{
    int price[] = { 60, 100, 120 };
    int weight[] = { 10, 20, 30 };
    printf("%f", fractional_knapsack(price, weight, 3, 50));
    return 0;
}