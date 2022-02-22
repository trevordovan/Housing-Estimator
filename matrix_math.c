#include "matrix_math.h"

double** create_matrix(int row, int col) {
    double **new_matrix;
    new_matrix = (double**)malloc(sizeof(double*) * row);
    int i;
    for (i = 0; i < row; ++i) {
        new_matrix[i] = (double*)malloc(sizeof(double) * col);
    }

    int j;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            new_matrix[i][j] = 0;
        }
    }
    return new_matrix;
}

void free_matrix(double **matrix, int row) {
    int i;
    for (i = 0; i < row; ++i) {
        free(matrix[i]);
    }
    free(matrix);
} 

void inverse_matrix(double **matrix, double **result, int size) {

    create_identity_matrix(result, size);   // initialize result to be idenity matrix

    int i, j;
    double pivot;

    for (i = 0; i < size; ++i) {            // convert to uppertriangular matrix
        pivot = matrix[i][i];
        multiply_or_divide_row(matrix, pivot, i, size, 1);
        multiply_or_divide_row(result, pivot, i, size, 1);
        
        for (j = i+1; j < size; ++j) {
            pivot = matrix[j][i];
            add_or_subtract_row(matrix, j, matrix[i], pivot, size, 1);
            add_or_subtract_row(result, j, result[i], pivot, size, 1);
        }
    }

    for (i = size-1; i >= 0; --i) {         // get all upper values to 0
        for (j = i-1; j >= 0; --j) {
            pivot = matrix[j][i];
            add_or_subtract_row(matrix, j, matrix[i], pivot, size, 1);
            add_or_subtract_row(result, j, result[i], pivot, size, 1);
        }
    }
}

void multiply_matrix(double **mat1, double **mat2, double **result, int row1, int col1, int row2, int col2) {

    // check if mat1 and mat2 are compabilte sizes
    if (col1 != row2) {
        printf("Matrices are incompatible\n");
        return;
    }

    // multiply mat1 by mat2 and store in result
    int i, j, k;
    for (i = 0; i < row1; ++i) {
        for (j = 0; j < col2; ++j) {
            for (k = 0; k < col1; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void transpose_matrix(double **mat, double** result, int row, int col) {
    int i, j;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            result[j][i] = mat[i][j];
        }
    }
}

void multiply_or_divide_row(double **matrix, double num, int row, int col_length, int div) {
    if (div == 1) {
        num = 1/num;
    }
    int i;
    for (i =0; i < col_length; ++i) { 
        matrix[row][i] *= num;
    }
}

void add_or_subtract_row(double **matrix, int row_location, double *row, double multiple, int col_length, int sub) {
    int i;
    if (sub == 1) {
        for (i = 0; i < col_length; ++i) {
            matrix[row_location][i] -= ( multiple * row[i] );
        }
    } 
    else {
        for (i = 0; i < col_length; ++i) {
            matrix[row_location][i] += ( multiple * row[i] );
        }
    }
}

void create_identity_matrix (double **result, int size) {
    int i, j, location = 0;
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            if (j == location) {
                result[i][j] = 1.0;
            }
            else {
                result[i][j] = 0.0;
            }
        }
        location++;
    }
}