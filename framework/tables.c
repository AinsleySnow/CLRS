#include <stdlib.h>

void** build_2d_table(int m, int n, size_t size)
{
    char** table = calloc(m, sizeof(char*));
    for (int i = 0; i < m; ++i)
        table[i] = calloc(n * size, sizeof(char));
    
    return (void**)table;
}

void release_2d_table(void** ptr, int m)
{
    for (int i = 0; i < m; ++i)
        free(ptr[i]);
    
    free(ptr);
}
