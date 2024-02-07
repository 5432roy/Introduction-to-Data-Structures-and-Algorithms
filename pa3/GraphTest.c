/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA3
*   GraphTest.c
*   Testing for Graph ADT with DFS
*****************************************************************************************/
#include<assert.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

void test_1() {
    printf("Starts test case 1: \n");
    /** initailize **/
    int n = 9;
    Graph G = newGraph(n);
    List L = newList();

    for(int i = 1; i <= n; i++) {
        append(L, i);
    }

    /*** constructs the graph ***/
    addArc(G, 1, 2);
    addArc(G, 1, 5);
    addArc(G, 2, 5);
    addArc(G, 4, 3);
    addArc(G, 5, 3);
    addArc(G, 5, 6);
    addArc(G, 6, 4);
    addArc(G, 7, 5);
    addArc(G, 7, 8);
    addArc(G, 8, 5);
    addArc(G, 8, 9);
    addArc(G, 9, 6);

    printf("Adjacency List of G:\n");
    printGraph(stdout, G);
    printf("\n");

    /*** Testing DFS() ***/
    DFS(G, L);
    
    // Testing Stack in DFS()
    printf("Stack expected:\n");
    printf("7 8 9 1 2 5 6 4 3\n");
    printf("Runtime Result: \n");
    printList(stdout, L);
    printf("\n\n");

    // Testing discover & finish time
    int discover_time[] = {1, 2, 4, 7, 3, 6, 13, 14, 15};
    int finish_time[] = {12, 11, 5, 8, 10, 9, 18, 17, 16};
    int parent[] = {NIL, 1, 5, 6, 2, 5, NIL, 7, 8};
    for(int i = 0; i < n; i++) {
        assert(getDiscover(G, i + 1) == discover_time[i]);
        assert(getFinish(G, i + 1) == finish_time[i]);
        assert(getParent(G, i + 1) == parent[i]);
    }
    printf("discover time & finish time & parent for all vertices are correct \n");

    // free the memory space
    freeGraph(&G);
    freeList(&L);
}

void test_2() {
    printf("\n*****************************\n");
    printf("Starts test case 2: \n");
    /** initailize **/
    int n = 8;
    Graph G = newGraph(n);
    List L = newList();

    for(int i = 1; i <= n; i++) {
        append(L, i);
    }

    /*** constructs the graph ***/
    addArc(G, 1, 2);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 5, 4);
    addArc(G, 5, 7);
    addArc(G, 5, 8);
    addArc(G, 6, 3);
    addArc(G, 1, 4);
    addArc(G, 6, 5);

    printf("Adjacency List of G:\n");
    printGraph(stdout, G);
    printf("\n");

    /*** Testing DFS() ***/
    DFS(G, L);

    // Testing Stack in DFS()
    printf("Stack expected:\n");
    printf("1 2 6 3 5 8 7 4\n");
    printf("Runtime Result: \n");
    printList(stdout, L);
    printf("\n\n");

    // Testing discover & finish time
    int discover_time[] = {1, 2, 12, 4, 3, 11, 6, 8};
    int finish_time[] = {16, 15, 13, 5, 10, 14, 7, 9};
    int parent[] = {NIL, 1, 6, 5, 2, 2, 5, 5};
    for(int i = 0; i < n; i++) {
        assert(getDiscover(G, i + 1) == discover_time[i]);
        assert(getFinish(G, i + 1) == finish_time[i]);
        assert(getParent(G, i + 1) == parent[i]);
    }
    printf("discover time & finish time & parent for all vertices are correct \n");
    // free the memory space
    freeGraph(&G);
    freeList(&L);
}

int main() {
    test_1();
    test_2();

    return 0;
}