#include "Matrix.h"
#include <stdlib.h>

int_matrix create_matrix(int row, int col)
{
    int** pprow = malloc(sizeof(int*) * row);
    for (int i = 0; i < row; ++i)
    {
        pprow[i] = malloc(sizeof(int) * col);
        for (int j = 0; j < col; ++j)
            pprow[i][j] = 0;
    }
        
    int_matrix ans = { pprow, row, col };
    return ans;
}

int_matrix matrix_multiply(int_matrix a, int_matrix b)
{ 
    if (a.ncol != b.nrow)
        return { NULL, 0, 0 };
   
    int_matrix ans = create_matrix(a.nrow, b.ncol);
    for (int i = 0; i < a.nrow; ++i)
        for (int j = 0; j < b.ncol; ++j)
            for (int k = 0; k < b.nrow; ++k)
                ans[i][j] += (a.row)[i][k] * (b.row)[k][j];

    return ans;
}

int_matrix matrix_add(int_matrix a, int_matrix b)
{
    if (a.ncol != b.ncol || a.nrow != b.nrow)
        return { NULL, 0, 0 };
    
    int_matrix ans = create_matrix(a.nrow, a.ncol);
    for (int i = 0; i < a.nrow; ++i)
        for (int j = 0; j < a.ncol; ++j)
            (ans.row)[i][j] = (a.row)[i][j] + (b.row)[i][j];
    
    return ans;
}