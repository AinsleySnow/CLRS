#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool find_universal_sink(int n, int matrix[][n])
{
    int i = 0, j = 0;

    while (i < n && j < n)
    {
        if (matrix[i][j] == 1) ++i;
        else ++j;
    }

    for (int k = 0; k < n; ++k)
    {
        if (matrix[i][k] == 1)
            return false;
        if (matrix[k][i] == 0 && k != i)
            return false;
    }
    return true;
}

int main(void)
{
    int matrix1[][6] = {
        { 0, 0, 0, 0, 0, 0 },
        { 1, 0, 0, 1, 0, 0 },
        { 1, 0, 1, 0, 1, 0 },
        { 1, 0, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 0 },
        { 1, 0, 1, 0, 1, 0 }
    };

    int matrix2[][6] = {
        { 0, 1, 0, 1, 0, 1 },
        { 1, 0, 0, 1, 0, 1 },
        { 1, 0, 1, 0, 1, 1 },
        { 1, 0, 0, 1, 0, 1 },
        { 1, 0, 0, 0, 0, 1 },
        { 0, 0, 0, 0, 0, 0 }
    };

    int matrix3[][6] = {
        { 0, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 1, 0, 0 },
        { 0, 0, 1, 0, 1, 1 },
        { 1, 0, 0, 1, 0, 0 },
        { 0, 0, 1, 0, 0, 1 },
        { 0, 0, 0, 0, 1, 0 }
    };

    printf("%d\n", find_universal_sink(6, matrix1));
    printf("%d\n", find_universal_sink(6, matrix2));
    printf("%d", find_universal_sink(6, matrix3));
    
    return 0;
}