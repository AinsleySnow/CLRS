#include <stdio.h>
#include <stdlib.h>

#define _ROOT_    0
#define _LEFT_    1
#define _RIGHT_   2

int** optimal_bst(float* prob_key, float* prob_dummy, int n)
{
    float** expect_cost = malloc(sizeof(float*) * (n + 2));
    for (int i = 0; i <= n + 1; ++i)
        expect_cost[i] = malloc(sizeof(float) * (n + 1));

    float** cost_without_level = malloc(sizeof(float*) * (n + 2));
    for (int i = 0; i <= n + 1; ++i)
        cost_without_level[i] = malloc(sizeof(float) * (n + 1));

    int** root = malloc(sizeof(int*) * (n + 1));
    for (int i = 0; i <= n; ++i)
        root[i] = malloc(sizeof(int) * (n + 1));
    

    for (int i = 1; i <= n + 1; ++i)
    {
        expect_cost[i][i - 1] = prob_dummy[i - 1];
        cost_without_level[i][i - 1] = prob_dummy[i - 1];
    }
    for (int len = 1; len <= n; ++len)
    {
        for (int i = 1; i <= n - len + 1; ++i)
        {
            int j = i + len - 1;
            expect_cost[i][j] = 0x7f800000;
            cost_without_level[i][j] = cost_without_level[i][j - 1] + prob_key[j] + prob_dummy[j];
            for (int r = i; r <= j; ++r)
            {
                float temp = expect_cost[i][r - 1] + expect_cost[r + 1][j] + cost_without_level[i][j];
                if (temp < expect_cost[i][j])
                {
                    expect_cost[i][j] = temp;
                    root[i][j] = r;
                }
            }
        }   
    }

    return root;
}

// Exercise 15.5-1
void construct_optimal_bst(int** root, int i, int j, int prev, int mode)
{
    if (j >= i)
    {
        int _root = root[i][j];
        if (mode == _ROOT_)
            printf("k%d is the root.\n", _root);
        else if (mode == _LEFT_)
            printf("k%d is the left child of k%d.\n", _root, prev);
        else if (mode == _RIGHT_)
            printf("k%d is the right child of k%d.\n", _root, prev);
        
        construct_optimal_bst(root, i, _root - 1, _root, _LEFT_);
        construct_optimal_bst(root, _root + 1, j, _root, _RIGHT_);
    }
    else
    {
        if (mode == _LEFT_)
            printf("d%d is the left child of k%d.\n", j, prev);
        else
            printf("d%d is the right child of k%d.\n", j, prev);
    }
}

int main(void)
{
    float probility_key[6] = { 0, 0.15, 0.10, 0.05, 0.10, 0.20 };
    float probility_dummy[6] = { 0.05, 0.10, 0.05, 0.05, 0.05, 0.10 };
    
    int** root_table = optimal_bst(probility_key, probility_dummy, 5);
    for (int i = 0; i <= 5; ++i)
    {
        for (int j = 0; j <= 5; ++j)
            printf("%4d ", root_table[i][j]);
        printf("\n");
    }
    
    construct_optimal_bst(root_table, 1, 5, 0, _ROOT_);

    return 0;
}