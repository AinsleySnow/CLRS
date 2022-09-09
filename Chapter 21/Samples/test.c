#include <stdio.h>
#include <memory.h>
#include "Disjoint.h"

int main(void)
{
    disjoint array[6];
    memset(array, 0, sizeof(disjoint) * 6);
    for (int i = 0; i < 6; ++i)
    {
        array[i].value = i + 'a';
        make_set(array + i);
    }

    union_set(array + 0, array + 1);
    union_set(array + 1, array + 2);
    union_set(array + 3, array + 4);
    union_set(array + 5, array + 4);
    
    for (int i = 0; i < 6; ++i)
        printf("%d\n", array[i].p - array);

    return 0;
}