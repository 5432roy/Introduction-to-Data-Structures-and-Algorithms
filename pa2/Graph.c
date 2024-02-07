/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA2
*   Graph.c 
*   Implementation file for Graph ADT
*****************************************************************************************/
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Graph.h"


/*** Struct ***/

typedef struct GraphObj {
    int order;
    int size;
    int source;
    // -1 >> haven't seen, 0 have seen but not yet visited, 1 = visited
    int *color;
    int *distance;
    int *parent;
    List *adjList;
} GraphObj;


/*** Constructors-Destructors ***/ 

Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));

    G->order = n;
    G->size = 0;
    G->source = NIL;

    G->color = calloc(n + 1, sizeof(int));
    G->distance = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->adjList = calloc(n + 1, sizeof(List));

    for(int i = 1; i <= n; i++) {
        G->color[i] = -1;
        G->distance[i] = INF;
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
        free(G->distance);
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
        printf("%s: vertex, %d, out of bound\n", caller, u);
        exit(EXIT_FAILURE);
    }
}

// Inserts the elements into the List in increasing order
void insertInOrder(List L, int u) {
    if(length(L) == 0) {
        append(L, u);
        return;
    }

    moveFront(L);
    while(index(L) != -1 && get(L) < u) {
        moveNext(L);
    }

    if(index(L) == -1) {
        append(L, u);
        return;
    }

    insertBefore(L, u);
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

int getSource(Graph G) {
    checkGraphExistence(G, "getSource");

    return (G->source);
} 

int getParent(Graph G, int u) {
    checkGraphExistence(G, "getParent");
    checkValidOrder(G, u, "getParent");

    return (G->parent[u]);
} 


int getDist(Graph G, int u) {
    checkGraphExistence(G, "getParent");
    checkValidOrder(G, u, "getParent");

    return (G->distance[u]);
} 

void getPath(List L, Graph G, int u) {
    checkGraphExistence(G, "getPath");
    checkValidOrder(G, u, "getPath");

    clear(L);

    if(getSource(G) == NIL) {
        printf("getPath(): Run BFS() first to run this function\n");
        exit(EXIT_FAILURE);
    }

    int source = getSource(G), current = u;

    while(current != source) {
        if(current == NIL) {
            clear(L);
            append(L, NIL);
            return;
        }
        prepend(L, current);
        current = getParent(G, current);
    }

    prepend(L, source);
} 


/*** Manipulation procedures ***/ 

void makeNull(Graph G) {
    checkGraphExistence(G, "makeNull");

    for(int i = 1; i <= getOrder(G); i++) {
        clear(G->adjList[i]);
        G->color[i] = -1;
        G->distance[i] = INF;
        G->parent[i] = NIL;
        G->adjList[i] = newList();
    }

    G->size = 0;
} 

void addEdge(Graph G, int u, int v) {
    checkGraphExistence(G, "addEdge");
    checkValidOrder(G, u, "addEdge");
    checkValidOrder(G, v, "addEdge");

    insertInOrder(G->adjList[u], v);
    insertInOrder(G->adjList[v], u);

    G->size += 1;
} 

void addArc(Graph G, int u, int v) {
    checkGraphExistence(G, "addArc");
    checkValidOrder(G, u, "addArc");
    checkValidOrder(G, v, "addArc");

    insertInOrder(G->adjList[u], v);

    G->size += 1;
} 

void BFS(Graph G, int s) {
    for(int i = 1; i <= getOrder(G); i++) {
        G->color[i] = -1;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }

    G->source = s;
    G->color[s] = 0;
    G->distance[s] = 0;

    // Uses this List L as a Queue to perform BFS
    List L = newList();
    append(L, s);

    while(length(L) > 0) {
        int cur = front(L);
        deleteFront(L);

        moveFront(G->adjList[cur]);

        for(int i = 0; i < length(G->adjList[cur]); i++) {
            int next = get(G->adjList[cur]);
            if(G->color[next] == -1) {
                G->color[next] = 0;
                G->distance[next] = G->distance[cur] + 1;
                G->parent[next] = cur;
                append(L, next);
            }
            moveNext(G->adjList[cur]);
        }

        G->color[cur] = 1;
    }

    freeList(&L);
} 


/*** Other operations ***/ 

void printGraph(FILE* out, Graph G) {
    checkGraphExistence(G, "printGraph");

    for(int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjList[i]);
        fprintf(out, "\n");
    }
} 
