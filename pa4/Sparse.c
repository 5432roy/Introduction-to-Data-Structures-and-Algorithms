/*
 *  Shang-Yu Chan 
 *  schan88
 *  2023 Fall CSE101 PA4
 *  Spare.c
 *  Main program of this project, 
 *  Reads two matrices from the input, produces the result including:
 *  Original matrix, Add, subtract, tranpose, product
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Matrix.h"

int main(int argc, char* argv[]) {

    // Checks that there are two command line arguments, otherwise stderr and quit
    
    if(argc != 3) {
        fprintf(stderr, "Usage: Lex <input file> <output file> \n");
        exit(EXIT_FAILURE);
    }

    // Opens files for reading and writing 
    
    FILE *output;

    output = fopen(argv[2], "w");
    if(output == NULL) {
        fprintf(stderr, "Unable to open file for writing\n");
        exit(EXIT_FAILURE);
    }
    
    FILE *input;

    input = fopen(argv[1], "r");
    if(input == NULL) {
        fprintf(stderr, "Unable to open file for reading\n");
        exit(EXIT_FAILURE);
    }

    // Reads the Matrices info from the input file

    int size, NNZ_A, NNZ_B;
    fscanf(input, "%d %d %d\n", &size, &NNZ_A, &NNZ_B);

    Matrix A = newMatrix(size), B = newMatrix(size);

    int row, col;
    double value;

    for(int i = 0; i < NNZ_A; i++) {
        fscanf(input, "%d %d %lf\n", &row, &col, &value);
        changeEntry(A, row, col, value);
    }

    for(int i = 0; i < NNZ_B; i++) {
        fscanf(input, "%d %d %lf\n", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    // Prints the result to output file

    // A
    fprintf(output, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(output, A);

    // B
    fprintf(output, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(output, B);

    // 1.5 * A
    Matrix scalar = scalarMult(1.5, A);
    fprintf(output, "(1.5)*A =\n");
    printMatrix(output, scalar);
    freeMatrix(&scalar);
    
    // A + B
    Matrix AplusB = sum(A, B);
    fprintf(output, "A+B =\n");
    printMatrix(output, AplusB);
    freeMatrix(&AplusB);
    
    // A + A
    Matrix AplusA = sum(A, A);
    fprintf(output, "A+A =\n");
    printMatrix(output, AplusA);
    freeMatrix(&AplusA);

    // B - A
    Matrix BminusA = diff(B, A);
    fprintf(output, "B-A =\n");
    printMatrix(output, BminusA);
    freeMatrix(&BminusA);

    // A - A
    Matrix AminusA = diff(A, A);
    fprintf(output, "A-A =\n");
    printMatrix(output, AminusA);
    freeMatrix(&AminusA);

    // transpose A
    Matrix transpose_A = transpose(A);
    fprintf(output, "Transpose(A) =\n");
    printMatrix(output, transpose_A);
    freeMatrix(&transpose_A);

    // product AB
    Matrix AB = product(A,B);
    fprintf(output, "A*B =\n");
    printMatrix(output, AB);
    freeMatrix(&AB);

    // product B^2
    Matrix BB = product(B,B);
    fprintf(output, "B*B =\n");
    printMatrix(output, BB);
    freeMatrix(&BB);

    freeMatrix(&A);
    freeMatrix(&B);

    fclose(output);
    fclose(input);
}
