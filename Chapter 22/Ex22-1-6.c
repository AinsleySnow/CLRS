#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool find_universal_sink(int** matrix)
{
    int i = 0, j = 0;
    int n = sizeof(matrix) / sizeof(int*);

    while (i < n || j < n)
    {
        if (i == j)
        {
            if (matrix[i][j] == 0)
                ++i;
            else
                ++j;
        }
        else
        {
            if (matrix[i][j] == 1)
                ++i;
            else
                ++j;
        }
    }

    for (int m = 0; m < n; ++m)
    {
        if (m != i)
        {
            if (matrix[i][m] != 0)
                return false;
            if (matrix[m][i] != 1)
                return false;
        }
        else
        {
            if (matrix[i][i] != 0)
                return false;
        }
    }
    return true;
}

int main(void)
{
    int matrix1[][6] = {
        { 0, 1, 0, 1, 0, 0 },
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

    printf("%d\n", find_universal_sink(matrix1));
    printf("%d", find_universal_sink(matrix2));
    
    return 0;
}