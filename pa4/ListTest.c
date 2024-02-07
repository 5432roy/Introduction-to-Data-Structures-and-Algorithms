/*
 *  Shang-Yu Chan 
 *  schan88
 *  2023 Fall CSE101 PA4
 *  ListTest.c
 *  Testing for List ADT that support generic type
*/

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

int main() {
    // Testing List with different type of elements in it
    List A = newList();

    for(int i = 0; i < 3; i++) {
        append(A, (newList()));
    }

    moveFront(A);
    
    double d1 = 1, d2 = 2, d3 = 3;
    int i1 = 1, i2 = 2, i3 = 3;

    append((List)get(A), &d1);
    append((List)(get(A)), &i1);
    moveNext(A);

    append((List)get(A), &d2);
    append((List)(get(A)), &i2);
    moveNext(A);

    append((List)get(A), &d3);
    append((List)(get(A)), &i3);

    moveFront(A);

    int i = 1;
    while(index(A) != -1) {
        List cur = (List)(get(A));
        moveFront(cur);
        assert(*(double*)get(cur) == (double)i);
        moveNext(cur);
        assert(*(int*)get(cur) == i);
        moveNext(A);
        i++;
        freeList(&cur);
    }

    clear(A);

    assert(length(A) == 0);

    char* str = "This is a string\n";
    append(A, str);

    moveFront(A);
    assert(strcmp("This is a string", (char*)get(A)));
    
    int i4 = 4;
    prepend(A, &i4);

    assert(length(A) == 2);

    int i5 = 5;
    append(A, &i5);

    assert(index(A) == 1);
    assert(strcmp("This is a string", (char*)get(A)));

    moveNext(A);
    assert(*(int*)get(A) == 5);

    deleteFront(A);
    assert(index(A) == 1);

    delete(A);
    assert(index(A) == -1);

    assert(strcmp("This is a string", (char*)front(A)));
    assert(strcmp("This is a string", (char*)back(A)));

    char* str2 = "This is a new string\n";

    moveBack(A);

    set(A, str2);
    assert(strcmp("This is a new string", (char*)get(A)));

    deleteBack(A);
    assert(length(A) == 0);
    assert(index(A) == -1);

    freeList(&A);

    printf("All tests passes!\n");

    return 0;
}