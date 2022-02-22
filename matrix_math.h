#ifndef matrix_math
#define matrix_math

/* 
 * Allocates memory for a new matrix. 
 * Assigns every element to 0.
 * @param  row # of rows for matrix
 * @param  col # of columns for matrix
 * @return new_matrix two dimensional array of doubles
 */
double** create_matrix(int row, int col);

/* Frees the memory of a given matrix. 
 * @param matrix matrix to be freed
 * @param row # of rows of matrix
 */
void free_matrix(double **matrix, int row);

/* 
 * Give matrix mat stores the inverse of mat in result. 
 * Assumes result is already correct size. Uses a simplifed 
 * Gauss Jordan elimination method.
 * @param matrix matrix to be inversed (must be a square matrix)
 * @param size size of rows and columns of mat
 * @param result location to store the inverse of mat
 */
void inverse_matrix(double **matrix, double **result, int size);

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
void multiply_matrix(double **mat1, double **mat2, double **result, int row1, int col1, int row2, int col2);

/* 
 * Given matrix mat stores tranpose of mat in result. 
 * Assumes result is already correct size.
 * @param mat matrix to be transposed
 * @param result location to store result of transposed matrix
 * @param row # of rows mat
 * @param col # of columns mat
 */
void transpose_matrix(double **mat, double** result, int row, int col);

/* 
 * Multiplies or divides a given matrix at a specific row.
 * @param matrix input matrix
 * @param num coefficent
 * @param row row of matrix to be multiplied or divided
 * @param col_length length of columns of input matrix
 * @param div boolean check 0 = multiply 1 = divide
 */
void multiply_or_divide_row(double **matrix, double num, int row, int col_length, int div);

/*
 * Adds or subtracts a multiple of one row from another.
 * @param matrix input matrix
 * @param row_location location for input matrix to perform calculation
 * @param row array of values in row
 * @param multiple coeffecient to be multipled to row
 * @param col_length length of columns of input matrix
 * @param sub boolean check = 0 add 1 = subtract
 */
void add_or_subtract_row(double **matrix, int row_location, double *row, double multiple, int col_length, int sub);

/* 
 * Creates an identity matrix of certain size. 
 * Assumes result is already correct size. 
 * @param result location created identity matrix is stored
 * @param size size of the rows and columns of identity matrix
 */
void create_identity_matrix (double **result, int size);

#endif
