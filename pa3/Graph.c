/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA3
*   Graph.c 
*   Implementation file for Graph ADT
*****************************************************************************************/
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Graph.h"

#define WHITE -1
#define GRAY 0
#define BLACK 1

/*** Struct ***/

typedef struct GraphObj {
    int order;
    int size;
    // -1 >> haven't seen, 0 have seen but not yet visited, 1 = visited
    int *color;
    int *discoverTime;
    int *finishTime;
    int *parent;
    List *adjList;


} GraphObj;


/*** Constructors-Destructors ***/ 

Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));

    G->order = n;
    G->size = 0;

    G->color = calloc(n + 1, sizeof(int));
    G->discoverTime = calloc(n + 1, sizeof(int));
    G->finishTime = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->adjList = calloc(n + 1, sizeof(List));

    for(int i = 1; i <= n; i++) {
        G->color[i] = WHITE;
        G->discoverTime[i] = UNDEF;
        G->finishTime[i] = UNDEF;
        G->parent[i] = NIL;
        G->adjList[i] = newList();
    }

    return G;
} 

void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL) {
        Graph G = *pG;

        for(int i = 1; i <= G->order; i++) {
            freeList(&(G->adjList[i]));
        }

        free(G->color);
        free(G->discoverTime);
        free(G->finishTime);
        free(G->parent);
        free(G->adjList);
        free(*pG);

        *pG = NULL;
    }
} 


/*** Helper functions ***/

// Checks if the given graph object G is valid
void checkGraphExistence(Graph G, char* caller) {
    if(G == NULL) {
        printf("%s: NULL Graph reference\n", caller);
        exit(EXIT_FAILURE);
    }
}

// Checks if the given vertex "u" is within the bound 1 <= u <= getOrder(G)
void checkValidOrder(Graph G, int u, char* caller) {
    if(u < 1 || u > G->order) {
        printf("%s: vertex: %d out of bound\n", caller, u);
        exit(EXIT_FAILURE);
    }
}

// Inserts the elements into the List in increasing order
int insertInOrder(List L, int u) {
    if(length(L) == 0) {
        append(L, u);
        return 1;
    }

    moveFront(L);
    while(index(L) != -1 && get(L) <= u) {
        if(get(L) == u) {
            return 0;
        }
        moveNext(L);
    }

    if(index(L) == -1) {
        append(L, u);
    } else {
        insertBefore(L, u);
    }

    return 1;
}


/*** Access functions ***/ 

int getOrder(Graph G) {
    checkGraphExistence(G, "getOrder");

    return (G->order);
}

int getSize(Graph G) {
    checkGraphExistence(G, "getSize");

    return (G->size);
} 

int getParent(Graph G, int u) {
    checkGraphExistence(G, "getParent");
    checkValidOrder(G, u, "getParent");

    return (G->parent[u]);
}

int getDiscover(Graph G, int u) {
    checkGraphExistence(G, "getDiscover");
    checkValidOrder(G, u, "getDiscover");

    return (G->discoverTime[u]);
}

int getFinish(Graph G, int u) {
    checkGraphExistence(G, "getFinish");
    checkValidOrder(G, u, "getFinish");

    return (G->finishTime[u]);
}


/*** Manipulation procedures ***/ 

void addEdge(Graph G, int u, int v) {
    checkGraphExistence(G, "addEdge");
    checkValidOrder(G, u, "addEdge");
    checkValidOrder(G, v, "addEdge");

    int a, b;
    a = insertInOrder(G->adjList[u], v);
    b = insertInOrder(G->adjList[v], u);

    G->size += (a & b);
} 

void addArc(Graph G, int u, int v) {
    checkGraphExistence(G, "addArc");
    checkValidOrder(G, u, "addArc");
    checkValidOrder(G, v, "addArc");

    G->size += insertInOrder(G->adjList[u], v);
}

void Visit(Graph G, List S, int* time, int v) {
    G->discoverTime[v] = ++(*time);
    G->color[v] = GRAY;

    List cur = G->adjList[v];
    moveFront(cur);

    while(index(cur) != -1) {
        if(G->color[get(cur)] == WHITE) {
            G->parent[get(cur)] = v;
            Visit(G, S, time, get(cur));
        }
        moveNext(cur);
    }
    G->color[v] = BLACK;
    G->finishTime[v] = ++(*time);
    prepend(S, v);
}

void DFS(Graph G, List S) {

    if(length(S) != getOrder(G)) {
        printf("error: length(S) != getOrder(G), DFS()\n");
        exit(EXIT_FAILURE);
    }

    // initialize the DFS tree
    for(int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discoverTime[i] = UNDEF;
        G->finishTime[i] = UNDEF;
    }

    int time = 0;
    // hold the sequence to discover the graph
    List seq = copyList(S);

    clear(S);

    moveFront(seq);
    while(index(seq) != -1) {
        if(G->color[get(seq)] == WHITE) {
            Visit(G, S, &time, get(seq));
        }
        moveNext(seq);
    }

    freeList(&seq);
}


/*** Other operations ***/ 

Graph transpose(Graph G) {
    checkGraphExistence(G, "transpose");

    Graph transpose_graph = newGraph(getOrder(G));

    for(int i = 1; i <= getOrder(G); i++) {
        List cur = G->adjList[i];
        moveFront(cur);
        while(index(cur) != -1) {
            addArc(transpose_graph, get(cur), i);
            moveNext(cur);
        }
    }
    return transpose_graph;
}

Graph copyGraph(Graph G) {
    checkGraphExistence(G, "copyGraph");

    Graph copy = newGraph(getOrder(G));

    for(int i = 1; i <= getOrder(G); i++) {
        List cur = G->adjList[i];
        moveFront(cur);
        while(index(cur) != -1) {
            addArc(copy, i, get(cur));
            moveNext(cur);
        }
    }

    return copy;
}

void printGraph(FILE* out, Graph G) {
    checkGraphExistence(G, "printGraph");

    for(int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjList[i]);
        fprintf(out, "\n");
    }
} 
