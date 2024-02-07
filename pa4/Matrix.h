/*
 *  Shang-Yu Chan 
 *  schan88
 *  2023 Fall CSE101 PA4
 *  Martix.c
 *  Header file for Square Martix ADT using List ADT
*/

#ifndef MATRIX_H_INCLUDE_
#define MATRIX_H_INCLUDE_

#include "List.h"

/*** Exported typs ***/

typedef struct MatrixObj *Matrix;


/*** Constructors & Desctructors ***/

// Returns a reference to a new n*n Matrix object in the zero state
Matrix newMatrix(int n);

// Frees heap memory associated with *pM, set *pM to NULL
void freeMatrix(Matrix* pM);


/*** Access functions ***/

// Returns the size of the square Matrix M
int size(Matrix M);

// Returns the number of non-zero elements in M
int NNZ(Matrix M);

// Returns true if matrices A and B are equal, false otherwise.
int equals(Matrix Ma, Matrix Mb);

/*** Manipulation procedures ***/

// Re-sets M to zero Matrix state
void makeZero(Matrix M);

// Changes the ith row, jth column of M to value x.
// Pre: 1 <= i, j <= size(M)
void changeEntry(Matrix M, int i, int j, double x);


/*** Matrix arithmetic operations ***/

// Returns a reference to a new Matrix object having the same entries as M.
Matrix copy(Matrix M);

// Returns a reference to a new Matrix object representing the transpose of M.
Matrix transpose(Matrix M);

// Returns a reference to a new Matrix object representing x*M.
Matrix scalarMult(double x, Matrix M);

// Returns a reference to a new Matrix object representing A + B.
// Pre: size(A) == size(B)
Matrix sum(Matrix A, Matrix B);

// Returns a reference to a new Matrix object representing A-B. 
// pre: size(A)==size(B) 
Matrix diff(Matrix A, Matrix B); 

// Returns a reference to a new Matrix object representing AB 
// pre: size(A)==size(B) 
Matrix product(Matrix A, Matrix B); 

// Prints a string representation of Matrix M to filestream out. Zero rows  
// are not printed.  Each non-zero row is represented as one line consisting  
// of the row number, followed by a colon, a space, then a space separated  
// list of pairs "(col, val)" giving the column numbers and non-zero values  
// in that row. The double val will be rounded to 1 decimal point. 
void printMatrix(FILE* out, Matrix M); 

#endif