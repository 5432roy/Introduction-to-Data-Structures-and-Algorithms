/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA2
*   Graph.h
*   Header file for Graph ADT
*****************************************************************************************/

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include "List.h"

#define INF -1
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
// Returns the most recently used source vertex in BFS(), or NIL if BFS() has not been called yet.
int getSource(Graph G); 
// Returns the parent of vertex u in the BFS tree created by BFS().
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u); 
// Returns the distance from the most recent BFS source to ertex u, or INF if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u); 
// Appends to the List L the vertices of a shortest path in G from source to u, or appedns to L the value NIL if no such path exists.
// Pre: getSource(G) != NIL, 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u); 


/*** Manipulation procedures ***/ 

// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G); 
// Inserts a new edge joining u to v. 
// Pre: 1 <= u, v <= getOrder(G)
void addEdge(Graph G, int u, int v); 
// Inserts a new directed edge from u to v.
// Pre: 1 <= u, v <= getOrder(G)
void addArc(Graph G, int u, int v); 
// Runs the BFS algorithm on the Graph G with source s, setting color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s); 


/*** Other operations ***/ 

// Prints the adjacency list representation of G to the file pointed to by out. 
void printGraph(FILE* out, Graph G); 

#endif
