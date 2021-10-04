#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_sets(float* points, float*** s)
{
    int n = sizeof(points) / sizeof(float);
    float** set = calloc(n, sizeof(float*));
    float* temp = calloc(n, sizeof(float));

    int left = 0, right = 1, i_set = 0, i_temp = 0;
    for (int i = 0; i < n; ++i)
    {
        if (points[i] < right && points[i] >= left)
        {
            temp[i_temp] = points[i];
            i_temp++;
        }
        else
        {
            left++;
            right++;
            set[i_set] = calloc(i_temp, sizeof(float));
            for (int j = 0; j < i_temp - 1; ++j)
                set[i_set][j] = temp[j];
            memset(temp, 0, n);
            i_temp = 0;
        }
    }

    *s = set;
}

int main(void)
{
    float points[] = { -0.1, 0.05, 0.2, 0.5, 0.56, 1, 1.2, 3.5, 7.4};
    float** output = NULL;
    find_sets(points, &output);

    for (int i = 0; output[i][0]; ++i)
    {
        printf("set %d:", i);
        for (int j = 0; output[i][j]; ++j)
            printf("%d ", output[i][j]);
    }

    for (int i = 0; i < 9; ++i)
        free(output[i]);
    free(output);
    return 0;
}