#include <stdio.h>
#include <string.h>

void faster_naive_matching(char* text, char* pattern, int n, int m)
{
    for (int i = 0, j = 0; i < n; ++i)
    {
        if (text[i] == pattern[j] && j < m)
            ++j;
        else
        {
            if (j != 0)
            {
                j = 0;
                --i;
            }
        }
        if (j == m)
        {
            printf("Pattern occurs with shift %d.\n", i - m + 1);
            j = 0;
        }
    }
}

int main(void)
{
    char text[] = "aabcaabccbcca";
    char pattern[] = "bcc";
    faster_naive_matching(text, pattern, 13, 3);
    return 0;
}