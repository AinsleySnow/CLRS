#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    stack s;
    create_stack(&s, 10);

    long data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for (int i = 0; i < 10; ++i)
        push(&s, data[i]);

    for (int i = 0; i < 8; ++i)
        printf("%ld ", pop(&s));
    
    clear_stack(&s);
    printf("\n%d\n", is_stack_empty(&s));

    return 0;
}