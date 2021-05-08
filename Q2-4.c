#include <stdio.h>
#include <stdlib.h>

int Merge(int *nums, int start, int end);
int FindInversion(int *nums, int start, int end);

int main(void)
{
    int num = 0;
    int *nums = NULL;
    scanf("%d", &num);
    nums = malloc(sizeof(int) * num);
    for (int i = 0; i < num; ++i)
        scanf("%d", nums[i]);

    printf("%d", FindInversion(nums, 0, num - 1));
}

int Merge(int *nums, int start, int end)
{
    int ans = 0;
    for (int i = start; i <= end / 2; ++i)
        if (nums[i] > nums[end - i])
            ++ans;
    return ans;
}

int FindInversion(int *nums, int start, int end)
{
    if (start != end)
    {
        int ans = 0;
        ans += FindInversion(nums, start, end / 2);
        ans += FindInversion(nums, end / 2 + 1, end);
        ans += Merge(nums, start, end);
        return ans;
    }
    else
        return 0;
}