#include <stdio.h>

void insertion_sort(int* const array, int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = array[i];
        int j = i;
        while (j > 0)
        {
            if (key >= array[j - 1])
                break;
            array[j] = array[j - 1];
            array[j - 1] = key;
            j -= 1;
        }
    }
}

int main(void)
{
    int array[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    insertion_sort(array, 10);
    for (int i = 0; i < 10; ++i)
        printf("%d ", array[i]);

    return 0;
}