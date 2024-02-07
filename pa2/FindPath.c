/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA2
*   FindPath.c
*   Client program in this Breadth First Search and Shortest Paths project
*****************************************************************************************/
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"


int main(int argc, char* argv[]) {

    // Checks that there are two command line arguments, otherwise stderr and quit
    
    if(argc != 3) {
        fprintf(stderr, "Usage: Lex <input file> <output file> \n");
        exit(EXIT_FAILURE);
    }

    // Opens files for reading and writing -----------------------------------------------------
    
    FILE *output;

    output = fopen(argv[2], "w");
    if(output == NULL) {
        fprintf(stderr, "Unable to open file for writing\n");
        exit(EXIT_FAILURE);
    }
    
    FILE *input;

    input = fopen(argv[1], "r");
    if(input == NULL) {
        fprintf(stderr, "Unable to open file for reading\n");
        exit(EXIT_FAILURE);
    }

    // Reads the Graph info from the input file

    int order;
    fscanf(input, "%d\n", &order);

    Graph G = newGraph(order);

    int u, v;
    fscanf(input, "%d %d\n", &u, &v);
    while((u + v)) {
        addEdge(G, u, v);
        fscanf(input, "%d %d\n", &u, &v);
    }

    // Prints the graph to output file

    printGraph(output, G);
    fprintf(output, "\n");

    // Reads the remaining pair from input and construct the BFS tree for each source/destination pairs.

    List L = newList();

    fscanf(input, "%d %d\n", &u, &v);
    while((u + v)) {
        BFS(G, u);
        getPath(L, G, v);
        int distance = getDist(G, v);

        if(distance == -1) {
            fprintf(output, "The distance from %d to %d is infinity\n", u, v);
            fprintf(output, "No %d-%d path exists\n\n", u, v);
        } else {
            fprintf(output, "The distance from %d to %d is %d\n", u, v, distance);
            fprintf(output, "A shortest %d-%d path is: ", u, v);
            printList(output, L);
            fprintf(output, "\n\n");
        }

        fscanf(input, "%d %d\n", &u, &v);
    }

    freeList(&L);
    freeGraph(&G);


    fclose(output);
    fclose(input);
}
