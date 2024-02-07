/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA1
*   Lex.c
*   Main program for this project
*****************************************************************************************/
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300 // maximum length of a string

int main(int argc, char* argv[]) {

    // Check that there are two command line arguments, otherwise stderr and quit
    
    if(argc != 3) {
        fprintf(stderr, "Usage: Lex <input file> <output file> \n");
        exit(EXIT_FAILURE);
    }


    // open output file for writing -----------------------------------------------------
    
    FILE *output;

    output = fopen(argv[2], "w");
    if(output == NULL) {
        fprintf(stderr, "Unable to open file for writing\n");
        exit(EXIT_FAILURE);
    }


    // open input files to get the number of the line -----------------------------------
    
    FILE *input;
    int line_count = 0;
    char string[MAX_LEN];

    input = fopen(argv[1], "r");
    if(input == NULL) {
        fprintf(stderr, "Unable to open file for reading\n");
        exit(EXIT_FAILURE);
    }

    while(fgets(string, MAX_LEN, input) != NULL) {
        line_count++;
    }

    fclose(input);


    // reopen input file for reading the string and put it into buffer ------------------
    
    input = fopen(argv[1], "r");
    if(input == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // the array that holds the string (char array)
    char** strings = calloc(line_count, sizeof(char*));

    // using this to get rid of unwanted trailing new line
    char tokenBuffer[MAX_LEN];
    char* token;

    for(int i = 0; i < line_count; i++) {
        if(fgets(string, MAX_LEN, input) == NULL) {
            fprintf(stderr, "Things went wrong while reading through file\n");
        }

        tokenBuffer[0] = '\0';
        token = strtok(string, " \n");
        
        while(token != NULL){
            strcat(tokenBuffer, token);
            token = strtok(NULL, "\n");
        }

        strings[i] = calloc(MAX_LEN, sizeof(char));

        strcpy(strings[i], string);
    }


    // Insertion sort with List ---------------------------------------------------------

    List L = newList();

    for(int i = 0; i < line_count; i++) {
        moveFront(L);

        if(length(L) == 0) {
            append(L, i);
            continue;
        }

        while(index(L) >= 0 && 
              index(L) < length(L) && 
              strcmp(strings[i], strings[get(L)]) > 0) {
            moveNext(L);
        }

        if(index(L) < 0) {
            append(L, i);
        } else {
            insertBefore(L, i);
        }

    }

    moveFront(L);

    for(int i = 0; i < line_count; i++) {
        fprintf(output, "%s\n", strings[get(L)]);
        moveNext(L);
    }

    freeList(&L);


    // free-up space --------------------------------------------------------------------
    for(int i = 0; i < line_count; i++) {
        free(strings[i]);
    }
    free(strings);


    // close files ----------------------------------------------------------------------
    fclose(input);
    fclose(output);

    return(0);
}
