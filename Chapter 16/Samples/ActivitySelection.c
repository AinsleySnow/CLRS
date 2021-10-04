#include <stdio.h>
#include <stdlib.h>

void recursive_activity_selector(const int start_time[], const int finish_time[], int output[], int i, int n, int i_out)
{
    output[i_out] = i;
    i++;
    while (start_time[i] < finish_time[output[i_out]])
        ++i;
    if (i < n)
        recursive_activity_selector(start_time, finish_time, output, i, n, i_out + 1);
    else
        return;
}

int* greedy_activity_selector(const int start_time[], const int finish_time[])
{
    int n = sizeof(start_time) / sizeof(int);
    int ans_index = 1, prev_activity = 0;
    int* ans = calloc(n, sizeof(int));
    ans[0] = 0;
    for (int i = 1; i < n; ++i)
    {
        if (start_time[i] > finish_time[prev_activity])
        {
            ans[ans_index++] = i;
            prev_activity = i;
        }
    }

    return ans;
}

int main()
{
    int s[] = { 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12 };
    int f[] = { 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16 };

    int* output = calloc(11, sizeof(int));
    recursive_activity_selector(s, f, output, 0, 11, 0);
    for (int i = 0; i < 11; ++i)
        printf("%d ", output[i]);

    printf("\n");
    free(output);

    output = greedy_activity_selector(s, f);
    for (int i = 0; i < 11; ++i)
        printf("%d ", output[i]);
    
    free(output);
    return 0;
}