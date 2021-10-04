#include <stdio.h>

void print_lcs(int** c, char* x, char* y, int i, int j)
{
    while (i > 0 && j > 0)
    {
        if (x[i - 1] == y[j - 1])
        {
            printf("%c", x[i - 1]);
            --i;
            --j;
        }
        else if (c[i][j - 1] >= c[i - 1][j])
            --j;
        else
            --i;
    }
}