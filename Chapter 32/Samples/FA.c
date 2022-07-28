#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void** build_2d_table(int, int, size_t);
void release_2d_table(void**, int);

inline int min(int a, int b)
{
    return a > b ? b : a;
}

bool is_suffix(char* p, char a, int k, int q)
{   
    if (k == -1)
        return true;
    if (p[k] != a)
        return false;

    k -= 1;
    for (; k >= 0; --k, --q)
        if (p[k] != p[q])
            return false;
    
    return true;
}

int** compute_transition_function(char* pattern, char* sigma)
{
    int m = strlen(pattern) + 1;
    int n = strlen(sigma);
    
    int** delta = build_2d_table(m, n, sizeof(int));

    for (int q = 0; q < m; ++q)
    {
        for (int i = 0; i < n; ++i)
        {
            int k = min(m + 1, q + 2);

            do
            {
                k -= 1;
            } while (!is_suffix(pattern, sigma[i], k - 1, q - 1));
            delta[q][i] = k == -1 ? 0 : k;
        }
    }

    return delta;
}

void print_table(int** table, int m, int n)
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf("%d ", table[i][j]);
        printf("\n");
    }
}

void finite_automaton_matcher(char* text, int** delta, int m)
{
    int length = strlen(text);
    int q = 0;

    for (int i = 0; i < length; ++i)
    {
        q = delta[q][text[i] - 'a'];
        if (q == m)
            printf("Pattern occurs with shift %d.\n", i - m + 1);
    }
}

int main(void)
{
    int** delta = compute_transition_function("ababaca", "abc");
    print_table(delta, 8, 3);
    printf("\n");
    finite_automaton_matcher("abababacaba", delta, 7);

    release_2d_table(delta, 8);
    return 0;
}