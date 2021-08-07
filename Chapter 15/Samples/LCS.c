#include <stdio.h>
#include <stdlib.h>

#define LEFT_UP     0
#define LEFT        1
#define UP          2

void lcs_length(char* x, char* y, int m, int n, int*** b, int*** c)
{
    *b = malloc(sizeof(int*) * (m + 1));
    for (int i = 0; i <= m; ++i)
        (*b)[i] = malloc(sizeof(int) * (n + 1));
    
    *c = malloc(sizeof(int*) * (m + 1));
    for (int i = 0; i <= m; ++i)
        (*c)[i] = malloc(sizeof(int) * (n + 1));
    
    for (int i = 1; i <= m; ++i)
        (*c)[i][0] = 0;
    for (int i = 0; i <= n; ++i)
        (*c)[0][i] = 0;

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (x[i - 1] == y[j - 1])
            {
                (*c)[i][j] = (*c)[i - 1][j - 1] + 1;
                (*b)[i][j] = LEFT_UP;
            }
            else if ((*c)[i - 1][j] >= (*c)[i][j - 1])
            {
                (*c)[i][j] = (*c)[i - 1][j];
                (*b)[i][j] = UP;
            }
            else
            {
                (*c)[i][j] = (*c)[i][j - 1];
                (*b)[i][j] = LEFT;
            }
        }
    }
}

void print_lcs(int** b, char* x, int i, int j)
{
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == LEFT_UP)
    {
        print_lcs(b, x, i - 1, j - 1);
        printf("%c", x[i - 1]);
    }
    else if (b[i][j] == UP)
        print_lcs(b, x, i - 1, j);
    else
        print_lcs(b, x, i, j - 1);
}

int main(void)
{
    int** b = NULL;
    int** c = NULL;
    char* x = "ABCBDAB";
    char* y = "BDCABA";
    int m = 7, n = 6;

    lcs_length(x, y, m, n, &b, &c);
    print_lcs(b, x, 7, 6);
    
    return 0;
}