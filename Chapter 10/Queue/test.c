#include <stdio.h>
#include "Queue.h"

int main(void)
{
    int data[10] = { 3, 4, 5, 6, 7, 8, 9, 1, 0, 2 };
    queue q = { NULL, NULL };
    for (int i = 0; i < 10; ++i)
        enqueue(&q, data[i]);
    printf("%d\n", is_empty(&q));
    for (int i = 0; i < 8; ++i)
        printf("%d ", dequeue(&q));
    
    free_queue(&q);
    return 0;
}