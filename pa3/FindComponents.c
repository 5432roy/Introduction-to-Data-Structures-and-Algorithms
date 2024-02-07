/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA3
*   FindPath.c
*   Client program that uses DFS() to find strongly connected component in the graph
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
        addArc(G, u, v);
        fscanf(input, "%d %d\n", &u, &v);
    }

    // Prints the graph to output file

    fprintf(output, "Adjacency list representation of G:\n");
    printGraph(output, G);
    fprintf(output, "\n");

    // Performs DFS
    
    List L = newList();    
    for(int i = 1; i <= getOrder(G); i++) {
        append(L, i);
    }
    DFS(G, L);

    Graph transpose_G = transpose(G);
    DFS(transpose_G, L);

    int strong_connected_comp_counts = 0;

    moveBack(L);
    while(index(L) != UNDEF) {
        if(getParent(transpose_G, get(L)) == NIL) {
           strong_connected_comp_counts += 1;
        }
        movePrev(L);
    }

    List *strong_connected_comps = calloc(strong_connected_comp_counts, sizeof(List));

    for(int i = 0; i < strong_connected_comp_counts; i++) {
        strong_connected_comps[i] = newList();
    }

    moveBack(L);
    for(int i = 0; i < strong_connected_comp_counts; i++) {
        while(index(L) != UNDEF) {
            if(getParent(transpose_G, get(L)) == NIL) {
                prepend(strong_connected_comps[i], get(L));
                movePrev(L);
                break;
            }
            prepend(strong_connected_comps[i], get(L));
            movePrev(L);

        }
    }

    fprintf(output, "G contains %d strongly connected components:\n",
            strong_connected_comp_counts);

    for(int i = 0; i < strong_connected_comp_counts; i++) {
        fprintf(output, "Component %d: ", i + 1);
        printList(output, strong_connected_comps[i]);
        fprintf(output, "\n");
    }


    freeList(&L);
    for(int i = 0; i < strong_connected_comp_counts; i++) {
        freeList(&strong_connected_comps[i]);
    }
    free(strong_connected_comps);
    freeGraph(&G);
    freeGraph(&transpose_G);


    fclose(output);
    fclose(input);
}
