/*
 *  Shang-Yu Chan 
 *  schan88
 *  2023 Fall CSE101 PA4
 *  Martix.c
 *  Implementation for Square Martix ADT using List ADT
*/

#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"

/*** structs ***/

// private Matrix type
typedef struct MatrixObj {
    List* row;
    int size;
    int non_zeros;
} MatrixObj;

// private Entry type
typedef struct EntryObj* Entry;

typedef struct EntryObj {
    int col;
    double value;
} EntryObj;


/*** Constructors & Destructors ***/

// Returns reference to new Entry object with given properties.
Entry newEntry(int col, double value) {
    Entry E = malloc(sizeof(EntryObj));
    E->col = col;
    E->value = value;

    return E;
}

// Frees heap memory pointed to by *pE, sets *pE to NULL.
void freeEntry(Entry* pE) {
    if(pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));

    M->size = n;
    M->non_zeros = 0;

    M->row = calloc(n + 1, sizeof(List));

    for(int i = 1; i <= n; i++) {
        M->row[i] = newList();
    }

    return M;
}

void freeMatrix(Matrix* pM) {
    // needs to clean the entry in List first
    makeZero(*pM);

    for(int i = 1; i <= size(*pM); i++) {
        freeList(&((*pM)->row[i]));
    }

    free((*pM)->row);
    free(*pM);

    *pM = NULL;
}

/*** Helper functions ***/

void checkMatrixExistence(Matrix M, char* func) {
    if(M == NULL) {
        printf("%s: NULL Martix reference\n", func);
        exit(EXIT_FAILURE);
    }
}

void checkMatricesSize(Matrix A, Matrix B, char* func) {
    if(size(A) != size(B)) {
        printf("%s: Size of Matrices not equal\n", func);
        exit(EXIT_FAILURE);
    }
}

void vectorAdd(Matrix res, int row, List vec1, List vec2) {
    moveFront(vec1);
    moveFront(vec2);

    while(index(vec1) != -1 || index(vec2) != -1) {
        if(index(vec1) != -1 && index(vec2) == -1) {
            Entry E = get(vec1);
            changeEntry(res, row, E->col, E->value);
            moveNext(vec1);
            continue;
        }

        if(index(vec1) == -1 && index(vec2) != -1) {
            Entry E = get(vec2);
            changeEntry(res, row, E->col, E->value);
            moveNext(vec2);
            continue;
        }

        Entry E1 = get(vec1), E2 = get(vec2);

        if(E1->col < E2->col) {
            changeEntry(res, row, E1->col, E1->value);
            moveNext(vec1);
            continue;
        }

        if(E1->col > E2->col) {
            changeEntry(res, row, E2->col, (E2->value));
            moveNext(vec2);
            continue;
        }

        if(E1->col == E2->col) {
            changeEntry(res, row, E1->col, (E1->value + E2->value));
            moveNext(vec1);
            moveNext(vec2);
        }
    }
}

void vectorDiff(Matrix res, int row, List vec1, List vec2) {
    moveFront(vec1);
    moveFront(vec2);

    while(index(vec1) != -1 || index(vec2) != -1) {
        if(index(vec1) != -1 && index(vec2) == -1) {
            Entry E = get(vec1);
            changeEntry(res, row, E->col, E->value);
            moveNext(vec1);
            continue;
        }

        if(index(vec1) == -1 && index(vec2) != -1) {
            Entry E = get(vec2);
            changeEntry(res, row, E->col, -(E->value));
            moveNext(vec2);
            continue;
        }

        Entry E1 = get(vec1), E2 = get(vec2);

        if(E1->col < E2->col) {
            changeEntry(res, row, E1->col, E1->value);
            moveNext(vec1);
            continue;
        }

        if(E1->col > E2->col) {
            changeEntry(res, row, E2->col, -(E2->value));
            moveNext(vec2);
            continue;
        }

        if(E1->col == E2->col) {
            changeEntry(res, row, E1->col, (E1->value - E2->value));
            moveNext(vec1);
            moveNext(vec2);
        }
    }
}

double vectorDot(List La, List Lb) {
    moveFront(La);
    moveFront(Lb);
    double res = 0;

    while(index(La) != -1 && index(Lb) != -1) {
        Entry Ea = get(La), Eb = get(Lb);

        if(Ea->col > Eb->col) {
            moveNext(Lb);
        }

        if(Ea->col < Eb->col) {
            moveNext(La);
        }

        if(Ea->col == Eb->col) {
            res += Ea->value * Eb->value;
            moveNext(La);
            moveNext(Lb);
        }
    }

    return res;
}

/*** Access functions ***/

int size(Matrix M) {
    checkMatrixExistence(M, "size");

    return M->size;
}

int NNZ(Matrix M) {
    checkMatrixExistence(M, "NNZ");

    return M->non_zeros;
}

int equals(Matrix Ma, Matrix Mb) {
    checkMatrixExistence(Ma, "equals");
    checkMatrixExistence(Mb, "equals");

    if(Ma->size != Mb->size) {
        return 0;
    }   

    for(int i = 1; i < size(Ma); i++) {
        List La = Ma->row[i], Lb = Mb->row[i];

        if(length(La) != length(Lb)) {
            return 0;
        }

        moveFront(La);
        moveFront(Lb);

        while(index(La) != -1) {
            Entry Ea = get(La), Eb = get(Lb);
            if(Ea->col != Eb->col || Ea->value != Eb->value) {
                return 0;
            }
            moveNext(La);
            moveNext(Lb);
        }
    }

    return 1;
}

void makeZero(Matrix M) {
    checkMatrixExistence(M, "makeZero");

    for(int i = 1; i <= size(M); i++) {
        List L = M->row[i];
        moveFront(L);
        while(index(L) != -1) {
            Entry E = get(L);
            freeEntry(&E);
            moveNext(L);
        }
        clear(L);
    }

    M->non_zeros = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
    checkMatrixExistence(M, "changeEntry");

    if(i < 1 || i > size(M)) {
        printf("changeEntry(): '%d' index out of bound '%d'\n", i, size(M));
        exit(EXIT_FAILURE);
    }
    if(j < 1 || j > size(M)) {
        printf("changeEntry(): '%d' index out of bound '%d'\n", j, size(M));
        exit(EXIT_FAILURE);
    }

    List L = M->row[i];

    if(x == 0) {
        moveFront(L);

        while(index(L) != -1) {
            Entry E = get(L);
            if(E->col == j) {
                freeEntry(&E);
                delete(L);
                M->non_zeros -= 1;
                break;
            }
            moveNext(L);
        }
    } else {
        if(length(L) == 0) {
            append(L, newEntry(j, x));
            M->non_zeros += 1;

        } else {
            moveFront(L);
            while(index(L) != -1 && ((Entry)get(L))->col < j) {
                moveNext(L);
            }

            if(index(L) != -1 && ((Entry)get(L))->col == j) {
                ((Entry)get(L))->value = x;
                return;
            }

            if(index(L) != -1) {
                insertBefore(L, newEntry(j, x));
                M->non_zeros += 1;
            }

            if(index(L) == -1) {
                append(L, newEntry(j, x));
                M->non_zeros += 1;
            }

        }
    }
}

/*** Matrix arithmetic operations ***/

Matrix copy(Matrix M) {
    checkMatrixExistence(M, "copy");

    Matrix copied = newMatrix(size(M));

    for(int i = 1; i <= size(M); i++) {
        List L = M->row[i];

        moveFront(L);

        while(index(L) != -1) {
            Entry E = get(L);
            changeEntry(copied, i, E->col, E->value);
            moveNext(L);
        }
    }

    return copied;
}

Matrix transpose(Matrix M) {
    checkMatrixExistence(M, "transpose");

    Matrix transpose_G = newMatrix(size(M));

    for(int row = 1; row <= size(M); row++) {
        List L = M->row[row];

        moveFront(L);

        while(index(L) != -1) {
            Entry E = get(L);
            changeEntry(transpose_G, E->col, row, E->value);
            moveNext(L);
        }
    }

    return transpose_G;
}

Matrix scalarMult(double x, Matrix M) {
    checkMatrixExistence(M, "scalarMult");

    Matrix new_M = newMatrix(size(M));

    if(x == 0) {
        return new_M;
    }

    for(int i = 1; i <= size(M); i++) {
        List L = M->row[i];
        
        moveFront(L);
        while(index(L) != -1) {
            Entry E = get(L);
            changeEntry(new_M, i, E->col, E->value * x);
            moveNext(L);
        }
    }

    return new_M;
}

Matrix sum(Matrix A, Matrix B) {
    checkMatrixExistence(A, "sum");
    checkMatrixExistence(B, "sum");
    checkMatricesSize(A, B, "sum");

    if(equals(A, B)) {
        return scalarMult(2, A);
    }

    Matrix new_M = newMatrix(size(A));


    for(int i = 1; i <= size(A); i++) {
        vectorAdd(new_M, i, A->row[i], B->row[i]);
    }

    return new_M;
}

Matrix diff(Matrix A, Matrix B) {
    checkMatrixExistence(A, "diff");
    checkMatrixExistence(B, "diff");
    checkMatricesSize(A, B, "diff");

    if(equals(A, B)) {
        return newMatrix(size(A));
    }

    Matrix new_M = newMatrix(size(A));

    for(int i = 1; i <= size(A); i++) {
        vectorDiff(new_M, i, A->row[i], B->row[i]);
    }

    return new_M;
}

Matrix product(Matrix A, Matrix B) {
    checkMatrixExistence(A, "product");
    checkMatrixExistence(B, "product");

    Matrix new_M = newMatrix(size(A)), transpose_B = transpose(B);

    for(int i = 1; i <= size(A); i++) {
        if(length(A->row[i]) == 0) {
            continue;
        }

        for(int j = 1; j <= size(transpose_B); j++) {
            if(length(transpose_B->row[j]) == 0) {
                continue;
            }
            changeEntry(new_M, i, j, vectorDot(A->row[i], transpose_B->row[j]));
        }
    }

    freeMatrix(&transpose_B);

    return new_M;
}


void printMatrix(FILE* out, Matrix M) {
    checkMatrixExistence(M, "printMatrix");

    for (int i = 1; i <= size(M); i++){
        List L = M->row[i];

        if (length(L) == 0){
            continue;
        }

        fprintf(out, "%d: ", i);

        moveFront(L);
        while(index(L) != -1) {
            Entry E = get(L);
            fprintf(out, "(%d, %0.1lf) ", E->col, E->value);    
            moveNext(L);
        }
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
}
