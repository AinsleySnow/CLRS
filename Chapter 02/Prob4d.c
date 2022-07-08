#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int Merge(int *nums, int start, int middle, int end);
int FindInversion(int *nums, int start, int end);

int main(void)
{
    int nums[5] = {5, 4, 3, 2, 1};
    printf("%d", FindInversion(nums, 0, 4));
    return 0;
}

int Merge(int *nums, int start, int middle, int end)
{
    int ans = 0;

    int _left = middle - start + 1;
    int _right = end - middle;
    int* left = calloc(_left + 1, sizeof(int));
    int* right = calloc(_right + 1, sizeof(int));

    for(int i = start, j = 0; i <= middle; ++i, ++j)
        left[j] = nums[i];
    for(int i = middle + 1, j = 0; i <= end; ++i, ++j)
        right[j] = nums[i];
    left[_left] = INT_MAX;
    right[_right] = INT_MAX;

    int leftPos = 0, rightPos = 0;
    for(int i = start; i <= end; ++i)
    {
        if(left[leftPos] <= right[rightPos])
            nums[i] = left[leftPos++];
        else
        {
            ans += _left - leftPos;
            nums[i] = right[rightPos++];
        }
    }

    free(left);
    left = NULL;
    free(right);
    right = NULL;

    return ans;
}

int FindInversion(int *nums, int start, int end)
{
    if (start != end)
    {
        int ans = 0;
        int middle = (end + start) / 2;
        ans += FindInversion(nums, start, middle); 
        ans += FindInversion(nums, middle + 1, end);
        ans += Merge(nums, start, middle, end);
        return ans;
    }
    else
        return 0;
}