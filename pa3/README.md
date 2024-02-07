# CSE101 Programming Assignment 3
This project is to build an Graph ADT in C and implement DFS() with it.

## Content
| File | Description | Note |
| ----------- | ----------- | ----------- |
| List.h | Header file for List ADT | | 
| List.c | Implementation file for List ADT | |
| Graph.h | Header file for Graph ADT | Only contains the functions that required for this project, no PA2 functions left  |
| Graph.c | Implementation file for Graph ADT | |
| GraphTest.c | Tests for Graph ADT | |
| FindComponents.c    | Main program for this project | |
| Makefile   | Read the comment in Makefile | |


## Implementation Details
For the `time` in `DFS() and Visit()`, `time` is implemented making the pointer of the time be a input varibale to Visit(). By doing so, `time` is only accessible from `DFS()` and `Visit()`, no other function would be able to modify it.

## Added Helper functions
- `checkGraphExistence`: Checks if the graph exists
- `checkValidOrder`: Checks if the input vertex is in range
- `insertInOrder`: Inserts element into the last in increasing order