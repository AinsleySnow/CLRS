#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct int_matrix
{
    int** row;
    int nrow;
    int ncol;
} int_matrix;

int_matrix create_matrix(int row, int col);
int_matrix matrix_mutilply(int_matrix a, int_matrix b);
int_matrix matrix_add(int_matrix a, int_matrix b);

#endif // _MATRIX_H_