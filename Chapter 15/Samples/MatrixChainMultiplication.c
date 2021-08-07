#include <stdio.h>
#include <stdlib.h>

void matrix_chain_order(int* sizes, int size_count, int*** separate)
{
    int n = size_count - 1;
    int** saved = malloc(sizeof(int*) * (n + 1));
    for (int i = 0; i <= n; ++i)
        saved[i] = malloc(sizeof(int) * (n + 1));

    (*separate) = malloc(sizeof(int*) * (n + 1));
    for (int i = 0; i <= n; ++i)
        (*separate)[i] = malloc(sizeof(int) * (n + 1));    
    
    for (int i = 1; i <= n; ++i)
        saved[i][i] = 0;

    for (int len = 2; len <= n; ++len)
    {
        for (int i = 1; i <= n - len + 1; ++i)
        {
            int j = i + len - 1;
            saved[i][j] = 0x7fffffff;
            int ans = 0;
            for (int k = i; k < j; ++k)
            {
                ans = saved[i][k] + saved[k + 1][j] + sizes[i - 1] * sizes[k] * sizes[j];
                if (ans < saved[i][j])
                {
                    saved[i][j] = ans;
                    (*separate)[i][j] = k;
                }
            }
        }
    }

    for (int i = 0; i <= n; ++i)
        free(saved[i]);
    free(saved);
}

void print_optimal_parens(int** sep, int i, int j)
{
    if (i == j)
        printf("A%d", i);
    else
    {
        printf("(");
        print_optimal_parens(sep, i, sep[i][j]);
        print_optimal_parens(sep, sep[i][j] + 1, j);
        printf(")");
    }
}

int main(void)
{
    int sizes[7] = { 30, 35, 15, 5, 10, 20, 25 };
    int** sep = NULL;
    matrix_chain_order(sizes, 7, &sep);
    print_optimal_parens(sep, 1, 6);

    for (int i = 0; i < 7; ++i)
        free(sep[i]);
    free(sep);
    return 0;
}