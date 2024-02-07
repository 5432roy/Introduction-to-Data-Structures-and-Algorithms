# CSE101 Programming Assignment 4
This project is to build an Matrix ADT in C using List ADT that supports generic type.

## Content
| File | Description | Note |
| ----------- | ----------- | ----------- |
| List.h | Header file for List ADT | | 
| List.c | Implementation file for List ADT | |
| ListTest.c | Tests for List ADT | Test cases are focusing on the modified features which is the change of `ListElement`|
| Matrix.h | Header file for Matrix ADT |   |
| Matrix.c | Implementation file for Graph ADT | For the private type of `MatrixObj`, there is a `int` field defined to help keep track of NNZ number |
| MatrixTest.c | Tests for Graph ADT | |
| Sparse.c    | Main program for this project | |
| Makefile   | Read the comment in Makefile | |


## Implementation Details
- `NNZ`: there is a `non_zeros` integer for `MatrixObj`. Since we should use and only use `changeEntry()` to modified the matrix, a correct implementation of `changeEntry()` would
make `NNZ()` become `O(1)` instead of `O(n^2)` where `n` is the size of the matrix

## Added Helper functions for Matrix ADT
- `void checkMatrixExistence(Matrix M, char* func)`: Checks if the Matrix reference exists. if not, exit()
- `void checkMatricesSize(Matrix A, Matrix B, char* func)`: Checks if the input vertex is in range. if not, exit()
- `void vectorAdd(Matrix res, int row, List vec1, List vec2)`: adds two vector (List) and put the value into given Matrix
- `void vectorDiff(Matrix res, int row, List vec1, List vec2)`: same helper function as `vectorAdd`
- `double vectorDot(List La, List Lb)`: returns the value of the dot product from two vector.