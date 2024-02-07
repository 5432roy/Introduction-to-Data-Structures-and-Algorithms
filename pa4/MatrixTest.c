/*
 *  Shang-Yu Chan 
 *  schan88
 *  2023 Fall CSE101 PA4
 *  MatrixTest.c
 *  Testing for Matrix ADT
*/

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

void test_1() {
    int n = 3;
    double r1[3][3] = {
        {1, 0, 5},
        {0, 4, 0},
        {0, 0, 7}
    };
    double r2[3][3] = {
        {9, 0, 55},
        {0, 0, 0},
        {-10, -8.7, 17}
    };
    double r3[3][3] = {
        {10, 0, 60},
        {0, 4, 0},
        {-10, -8.7, 24}
    };
    double r4[3][3] = {
        {-8, 0, -50},
        {0, 4, 0},
        {10, 8.7, -10}
    };

    Matrix M1 = newMatrix(n), M2 = newMatrix(n), sum_res = newMatrix(n), diff_res = newMatrix(n);
    Matrix temp;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            changeEntry(M1, i, j, r1[i - 1][j - 1]);
            changeEntry(M2, i, j, r2[i - 1][j - 1]);
            changeEntry(sum_res, i, j, r3[i - 1][j - 1]);
            changeEntry(diff_res, i, j, r4[i - 1][j - 1]);
        }
    }

    temp = sum(M1, M2);
    assert(equals(sum_res, temp));

    freeMatrix(&temp);

    temp = diff(M1, M2);
    assert(equals(diff_res, temp));

    freeMatrix(&temp);

    freeMatrix(&M1);
    freeMatrix(&M2);
    freeMatrix(&sum_res);
    freeMatrix(&diff_res);
}

void test_2() {
    int n = 10;
    // the matrix for random_M
    double r[10][10] = {
        {1, 6, 8, 1, 2, 0, 5, 0, 0, 0}, 
        {0, 0, 0, 5, 0, 1, 0, 6, 0, 8}, 
        {0, 7, 0, 9, 1, 0, 0, 0, 5, 0}, 
        {0, 0, 6, 0, 0, 4, 8, 8, 4, 3}, 
        {3, 3, 2, 9, 8, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 4, 0, 1, 0, 6, 0}, 
        {2, 8, 0, 8, 0, 4, 7, 0, 0, 9}, 
        {0, 0, 0, 4, 0, 8, 0, 7, 0, 6}, 
        {0, 0, 0, 4, 0, 2, 0, 3, 0, 1}, 
        {0, 0, 5, 0, 2, 0, 1, 0, 4, 0}
    };
    // the expected transpose matrix for random_M
    double t[10][10] = {
        {1, 0, 0, 0, 3, 0, 2, 0, 0, 0},
        {6, 0, 7, 0, 3, 0, 8, 0, 0, 0},
        {8, 0, 0, 6, 2, 0, 0, 0, 0, 5},
        {1, 5, 9, 0, 9, 0, 8, 4, 4, 0},
        {2, 0, 1, 0, 8, 4, 0, 0, 0, 2},
        {0, 1, 0, 4, 0, 0, 4, 8, 2, 0},
        {5, 0, 0, 8, 0, 1, 7, 0, 0, 1},
        {0, 6, 0, 8, 0, 0, 0, 7, 3, 0},
        {0, 0, 5, 4, 0, 6, 0, 0, 0, 4},
        {0, 8, 0, 3, 0, 0, 9, 6, 1, 0}
    };

    // identify matrix
    Matrix identify_M = newMatrix(n), scalarMatirx_2 = newMatrix(n), random_M = newMatrix(n), transpose_M = newMatrix(n);
    Matrix M, M2;

    for(int i = 1; i <= n; i++) {
        changeEntry(identify_M, i, i, 1);
        changeEntry(scalarMatirx_2, i, i, 2);
        for(int j = 1; j <= n; j++) {
            changeEntry(random_M, i, j, r[i - 1][j - 1]);
            changeEntry(transpose_M, i, j, t[i - 1][j - 1]);
        }
    }

    printf("identify matrix: \n");
    printMatrix(stdout, identify_M);
    assert(size(identify_M) == 10);
    assert(NNZ(identify_M) == 10);

    printf("scalar matrix that multiple its target by 2: \n");
    printMatrix(stdout, scalarMatirx_2);
    assert(size(scalarMatirx_2) == 10);
    assert(NNZ(scalarMatirx_2) == 10);


    M = copy(identify_M);
    assert(equals(M, identify_M));

    freeMatrix(&M);

    M = scalarMult(2, identify_M);

    // 2 * identify matrix * A = 2 * A
    assert(NNZ(M) == 10);
    assert(size(M) == 10);
    assert(equals(M, scalarMatirx_2));

    makeZero(M);

    assert(NNZ(M) == 0);

    freeMatrix(&M);

    M = transpose(random_M);
    printf("M: \n");
    printMatrix(stdout, M);
    printf("tranpose_M: \n");
    printMatrix(stdout, transpose_M);

    // A^T = A^T
    assert(equals(M, transpose_M));

    freeMatrix(&M);

    M = transpose(transpose_M);

    // (A^T)^T = A
    assert(equals(M, random_M));

    freeMatrix(&M);

    // M = A * A^T
    M = product(random_M, transpose_M);

    // M2 = (A * A^T) ^ T = A^T * A
    M2 = transpose(M);

    assert(equals(M, M2));

    freeMatrix(&identify_M);
    freeMatrix(&scalarMatirx_2);
    freeMatrix(&random_M);
    freeMatrix(&transpose_M);
    freeMatrix(&M);
    freeMatrix(&M2);
}

int main() {
    printf("Begin tests\n");
    printf("*************************************\n");
    test_1();
    test_2();
    printf("*************************************\n");
    printf("all tests passed with assert()\n");

    return EXIT_SUCCESS;
}