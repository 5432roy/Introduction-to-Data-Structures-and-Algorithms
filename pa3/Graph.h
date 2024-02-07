/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA3
*   Graph.h
*   Header file for Graph ADT with the implementation of DFS
*****************************************************************************************/

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include "List.h"

#define UNDEF -1
#define NIL 0


/*** Exported types ***/

typedef struct GraphObj* Graph;


/*** Constructors-Destructors ***/ 

// Returns reference to new empty Graph object. 
Graph newGraph(int n); 
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG); 


/*** Access functions ***/ 

// Returns the order value in graph.
int getOrder(Graph G); 
// Returns the number of elements in graph.
int getSize(Graph G); 
// Returns the parent of vertex u in the BFS tree created by DFS(). Default NIL.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u); 
// Returns the discovered time for the vertex u. Default UNDEF.
// Pre: 1 < u <= getOrder(u)
int getDiscover(Graph G, int u);
// Returns the finished time for the vertex u. Default UNDEF.
// Pre: 1 < u <= getOrder(u)
int getFinish(Graph G, int u);


/*** Manipulation procedures ***/ 

// Inserts a new edge joining u to v. 
// Pre: 1 <= u, v <= getOrder(G)
void addEdge(Graph G, int u, int v); 
// Inserts a new directed edge from u to v.
// Pre: 1 <= u, v <= getOrder(G)
void addArc(Graph G, int u, int v); 
// Runs the DFS algorithm on the Graph G with source s, setting color, distance, parent, and source fields of G accordingly.
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S); 


/*** Other operations ***/ 

// Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);
// Retruns a reference to a new graph that is a copy of G.
Graph copyGraph(Graph G);
// Prints the adjacency list representation of G to the file pointed to by out. 
void printGraph(FILE* out, Graph G); 

#endif
