/* 
 * @author - Trevor Dovan
 *
 * STOP using ints for anything but rows and coluumns!
 * 
 * Extensively test functions in ALL SCENARIOS (vectors, square and nonsquare matrices)
 */

#include <stdlib.h>
#include <stdio.h>

double** create_matrix();       // allocates memory for matrix (could cause memory leaks if not used carefully)
void free_matrix();             // frees the memory allocated to a specified matrix
void create_identity_matrix();  // creates an identity matrix of size n
void print();                   // prints matrix of size row x col
void multiply_matrix();         // multiplies matrix1 x matrix2
void transpose_matrix();        // creates transpose of matrix
void multiply_or_divide_row();  // multiplies or divides all elements of specific row
void add_or_subtract_row();     // adds or subtracts multiple of one row from another
void inverse_matrix();          // creates inverse of matrix
void get_weights();             // algorithm to generate weights from given training data

/* 
 * Allocates memory for a new matrix. 
 * Assigns every element to 0.
 * @param  row # of rows for matrix
 * @param  col # of columns for matrix
 * @return new_matrix two dimensional array of doubles
 */
double** create_matrix(int row, int col) {
    double **new_matrix;
    new_matrix = (double**)malloc(sizeof(double*) * row);
    int i;
    for (i = 0; i < row; ++i) {
        new_matrix[i] = (double*)malloc(sizeof(double) * col);
    }

    // does this do anything? Seems to solve all rounding and weird output problems
    int j;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            new_matrix[i][j] = 0;
        }
    }
    return new_matrix;
}

/* Frees the memory of a given matrix. 
 * @param matrix matrix to be freed
 * @param row # of rows of matrix
 */
void free_matrix(double **matrix, int row) {
    int i;
    for (i = 0; i < row; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

/* 
 * Creates an identity matrix of certain size. 
 * Assumes result is already correct size. 
 * @param result location created identity matrix is stored
 * @param size size of the rows and columns of identity matrix
 */
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

/* 
 * Given matrices mat1 and mat2 stores the 
 * product of mat1 and mat2 in result. 
 * Assumes result is already correct size.
 * @param result matrix where product is stored
 * @param mat2 matrix 2
 * @param mat1 matrix 1
 * @param row1 # of rows mat1
 * @param col1 # of columms mat1
 * @param row2 # of rows mat2
 * @param col2 # of columms mat2
 */
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

/* 
 * Given matrix mat stores tranpose of mat in result. 
 * Assumes result is already correct size.
 * @param mat matrix to be transposed
 * @param result location to store result of transposed matrix
 * @param row # of rows mat
 * @param col # of columns mat
 */
void transpose_matrix(double **mat, double** result, int row, int col) {
    int i, j;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            result[j][i] = mat[i][j];
        }
    }
}

/* 
 * Multiplies or divides a given matrix at a specific row.
 * @param matrix input matrix
 * @param num coefficent
 * @param row row of matrix to be multiplied or divided
 * @param col_length length of columns of input matrix
 * @param div boolean check 0 = multiply 1 = divide
 */
void multiply_or_divide_row(double **matrix, double num, int row, int col_length, int div) {
    if (div == 1) {
        num = 1/num;
    }
    int i;
    for (i =0; i < col_length; ++i) { 
        matrix[row][i] *= num;
    }
}

/*
 * Adds or subtracts a multiple of one row from another.
 * @param matrix input matrix
 * @param row_location location for input matrix to perform calculation
 * @param row array of values in row
 * @param multiple coeffecient to be multipled to row
 * @param col_length length of columns of input matrix
 * @param sub boolean check = 0 add 1 = subtract
 */
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

/* 
 * Give matrix mat stores the inverse of mat in result. 
 * Assumes result is already correct size. Uses a simplifed 
 * Gauss Jordan elimination method.
 * @param matrix matrix to be inversed (must be a square matrix)
 * @param size size of rows and columns of mat
 * @param result location to store the inverse of mat
 */
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

// 0 = test main, 1 = pa2 main
#if 1

int main(int argc, char **argv) {
    
    char* filename = argv[1];                           // Open training file
    FILE *file = fopen(filename, "r");
    int row, col, i, j;
    char* type = malloc(sizeof(char) * 6);
    fscanf(file, "%s", type);

    if (type[0] != 't') {                               // check if input is training
        return EXIT_FAILURE;
    }

    fscanf(file, "%d%d", &col, &row);                   // add 1 to col to account for X[i][0] being all ones
    col++;

    double **X = create_matrix(row, col);               // allocate memory for X, Y, and W
    double **Y = create_matrix(row, 1);
    double **W = create_matrix(col, 1);

    for (i = 0; i < row; ++i) {                         // populate X and Y
        for (j = 0; j < col; ++j) {
            if(j == 0){
                X[i][j] = 1;
                continue;
            }
            else if (j == col-1) {
                fscanf(file, "%lf", &X[i][j]);
                fscanf(file, "%lf", &Y[i][0]);
                continue;
            }
            fscanf(file, "%lf", &X[i][j]);
        }
    }
    fclose(file);

    filename = argv[2];                                 // Open data file
    file = fopen(filename, "r");
    int row2, col2;
    fscanf(file, "%s", type);

    if (type[0] != 'd') {                               // check if input is data
        return EXIT_FAILURE;   
    }

    free(type);

    fscanf(file, "%d%d", &col2, &row2);                 // add 1 to col to account for data[i][0] being all ones
    col2++;

    if (col != col2) {                                  // necessary check?
        return EXIT_FAILURE;
    }

    double **data_matrix = create_matrix(row2, col2);   // allocate memory for data matrix

    for (i = 0; i < row2; ++i) {                        // populate
        for (j = 0; j < col2; ++j) {
            if(j == 0){
                data_matrix[i][j] = 1;
                continue;
            }
            fscanf(file, "%lf", &data_matrix[i][j]);
        }
    }
    fclose(file);

    get_weights(X, Y, W, row, col);                     // train data 

    double **estimate = create_matrix(row2, 1);         // get estimates
    multiply_matrix(data_matrix, W, estimate, row2, col2, col, 1);

    print(estimate, row2, 1);

    free_matrix(X, row);                               // free all
    free_matrix(Y, row);
    free_matrix(W, col);
    free_matrix(data_matrix, row2);
    free_matrix(estimate, row2);

    return EXIT_SUCCESS;
}

#else

/* 
 * This main is used for testing functions. It will take in matrices 
 * from a txt file and store them in double** arrays. Arrays of all 
 * sizes and combinations should be tested to ensure proper outputs 
 * from all functions.
 */
int main(int argc, char **argv) {

    // 0 = 1 file, 1 = 2 files
    #if 0
    
    char* filename = argv[1];                                // Open file 1
    FILE *file = fopen(filename, "r");
    int row1, col1, i, j;
    fscanf(file, "%d%d", &row1, &col1);
    //printf("%d \n", col1);s

    double **matrix1 = create_matrix(row1, col1);;           // allocate memory for matrix1
    
    for (i = 0; i < row1; ++i) {                             // populate
        for (j = 0; j < col1; ++j) {
            fscanf(file, "%lf", &matrix1[i][j]);
        }
    }
    fclose(file);

    filename = argv[2];                                      // Open file 2
    file = fopen(filename, "r");
    int row2, col2;
    fscanf(file, "%d%d", &row2, &col2);

    double **matrix2 = create_matrix(row2, col2);;           // allocate memory for matrix2
    
    for (i = 0; i < row2; ++i) {                             // populate
        for (j = 0; j < col2; ++j) {
            fscanf(file, "%lf", &matrix2[i][j]);
        }
    }
    fclose(file);

    //testing
    
    //double **result = create_matrix(row1, col2);

    //multiply_matrix(matrix1, matrix2, result, row1, col1, row2, col2);    // good
    //transpose_matrix(matrix1, result, row1, col1);                        // good
    //add_or_subtract_row(matrix1, matrix1[0], 2, 1, 1);                    // good
    //multiply_or_divide_row(matrix1, 2, 1, 1, 1);                          // good
    print(matrix1, row1, col1);
    //print(matrix2, row2, col2);
    //print(result, row1, col2);

    #else

    char* filename = argv[1];                                // Open file 1
    FILE *file = fopen(filename, "r");
    int row1, col1, i, j;
    fscanf(file, "%d%d", &row1, &col1);

    double **matrix1 = create_matrix(row1, col1);            // allocate memory for matrix1
    
    for (i = 0; i < row1; ++i) {                             // populate
        for (j = 0; j < col1; ++j) {
            fscanf(file, "%lf", &matrix1[i][j]);
        }
    }
    fclose(file);

    //testing

    double **result = create_matrix(row1, col1);            // allocate for result
    
    print(matrix1, row1, col1);
    inverse_matrix(matrix1, result, row1); // good (not fully tested)
    print(matrix1, row1, col1);
    print(result, row1, col1);

    #endif

    return EXIT_SUCCESS;
}

#endif