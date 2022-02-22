#include <stdio.h>
#include <stdlib.h>
#include "matrix_math.h"

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