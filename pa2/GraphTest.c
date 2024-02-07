/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA2
*   GraphTest.c
*   Testing for Graph ADT
*****************************************************************************************/
#include<assert.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

int main() {
    int n = 10;
    Graph G = newGraph(n);
    List L = newList();

    assert(getOrder(G) == n);
    assert(getSize(G) == 0);
    assert(getSource(G) == NIL);

    for(int i = 1; i < n; i++) {
        addEdge(G, i, i + 1);
    }

    BFS(G, 1);
    getPath(L, G, n);

    // Expects 1 to n.
    printList(stdout, L);
    printf("\n");

    assert(getSize(G) == n - 1);
    assert(getSource(G) == 1);

    // Expects a graph that every vertices are connected with +-1 index.
    printGraph(stdout, G);
    printf("\n");

    makeNull(G);

    assert(getOrder(G) == n);
    assert(getSize(G) == 0);
    assert(getSource(G) == 1);
    assert(getParent(G, 2) == NIL);

    // Expects printing nothing.
    printGraph(stdout, G);
    printf("\n");

    for(int i = 1; i < n; i++) {
        addArc(G, i, i + 1);
    }

    BFS(G, n / 2);

    // Expects a graph that only smaller index vertices can reach the larger index vertices.
    printGraph(stdout, G);
    printf("\n");

    assert(getDist(G, 1) == INF);
    assert(getDist(G, n / 2 + 1) == 1);
    assert(getParent(G, 2) == NIL);

    freeGraph(&G);

    assert(G == NULL);
}