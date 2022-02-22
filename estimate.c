#include <stdlib.h>
#include <stdio.h>
#include "matrix_math.h"

void print();                   // prints matrix of size row x col
void get_weights();             // algorithm to generate weights from given training data

/*
 * Given matrix X (attributes) and Y (prices) finds a
 * vector W that relate X and Y. W = (X^T X)^−1 X^T Y
 * @param X matrix of attributes (m x n)
 * @param Y vector of prices
 * @param W result vector
 * @param row # of rows of X and Y
 * @param col # of columns of X
 */
void get_weights(double **X, double **Y, double **W, int row, int col) {
    
    double **X_transpose = create_matrix(col, row);                                 // X transposed (n x m)
    transpose_matrix(X, X_transpose, row, col);                 

    double **temp_matrix = create_matrix(col, col);                                 // X transposed times X (n x n)
    multiply_matrix(X_transpose, X, temp_matrix, col, row, row, col);

    double **temp2_matrix = create_matrix(col, col);                                // inverse of X transposed times X (n x n)
    inverse_matrix(temp_matrix, temp2_matrix, col);

    double **temp3_matrix = create_matrix(col, row);                                // inverse times X transposed (n x m)
    multiply_matrix(temp2_matrix, X_transpose, temp3_matrix, col, col, col, row);
    
    multiply_matrix(temp3_matrix, Y, W, col, row, row, 1);                          // ^that times Y, store in W

    free_matrix(X_transpose, col);                                                  // free all 
    free_matrix(temp_matrix, col);
    free_matrix(temp2_matrix, col);
    free_matrix(temp3_matrix, col);
}

/* 
 * Prints a matrix of size row x col
 * @param matrix input matrix to be printed
 * @param row # of rows of matrix
 * @param col # of columns of matrix
 */
void print(double **matrix, int row, int col) {
    int i, j;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; j++) {
            if (j == col-1) {
                printf("%.0f", matrix[i][j]);
            }
            else {
                printf("%.0f ", matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}