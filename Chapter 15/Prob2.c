#include <stdio.h>
#include <stdlib.h>

#define reverse_index(x, n) ((n) - (x))

int** para_length(const char* x)
{
    int table_size = strlen(x) + 1;
    int** saved = malloc(sizeof(int*) * table_size);
    for (int i = 0; i < table_size; ++i)
        saved[i] = malloc(sizeof(int) * table_size);

    for (int i = 0; i < table_size; ++i)
        saved[0][i] = 0;
    for (int i = 0; i < table_size; ++i)
        saved[i][0] = 0;

    for (int i = 1; i < table_size; ++i)
    {
        for (int j = 1; j < table_size; ++j)
        {
            if (x[i - 1] == x[reverse_index(j - 1, table_size - 2)])
                saved[i][j] = saved[i - 1][j - 1] + 1;
            else if (saved[i - 1][j] >= saved[i][j - 1])
                saved[i][j] = saved[i - 1][j];
            else
                saved[i][j] = saved[i][j - 1];
        }
    }

    return saved;
}

int main(void)
{
    char* x = "character";
    int** saved_table = para_length(x);

    int i = 9, j = 9;
    while (i > 0 && j > 0)
    {
        if (x[i - 1] == x[reverse_index(j - 1, 8)])
        {
            printf("%c", x[i - 1]);
            --i;
            --j;
        }
        else if (saved_table[i][j - 1] >= saved_table[i - 1][j])
            --j;
        else
            --i;
    }

    for (int i = 0; i < 10; ++i)
        free(saved_table[i]);
    free(saved_table);
    return 0;
}