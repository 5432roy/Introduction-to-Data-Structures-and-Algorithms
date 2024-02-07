/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA1
*   List.h
*   Header file for List ADT
*****************************************************************************************/

#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include<stdbool.h>

#define FORMAT "%d "  // format string for ListElement


// Exported types -----------------------------------------------------------------------

typedef int ListElement;
typedef struct ListObj* List;


// Constructors-Destructors -------------------------------------------------------------

// Returns reference to new empty List object. 
List newList();

// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions ---------------------------------------------------------------------

// Returns the number of elements in L.
int length(List L); 
// Returns index of cursor element if defined, -1 otherwise. 
int index(List L);  
// Returns front element of L. Pre: length()>0 
ListElement front(List L);  
// Returns back element of L. Pre: length()>0 
ListElement back(List L);   
// Returns cursor element of L. Pre: length()>0, index()>=0 
ListElement get(List L);    
// Returns true iff Lists A and B are in same state, otherwise return false
bool equals(List A, List B); 

// Manipulation procedures --------------------------------------------------------------

// Resets L to its original empty state.
void clear(List L); 
// Overwrites the cursor element's data with x. Pre: length() > 0, index >= 0
void set(List L, ListElement x);
// If L is not empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L);
// If L is not empty, sets cursor under the back element, otherwise does nothing.
void movBack(List L);
/* 
*   If cursor is defined and not at front, move cursor one step toward the front of L.
*   If cursor is defined and at front, cursor becomes undefined.
*   If cursor is undefined, do nothing.
*/ 
void movePrev(List L);
/* 
*   If cursor is defined and not at back, move cursor one step toward the back of L.
*   If cursor is defined and at back, cursor becomes undefined.
*   If cursor is undefined, do nothing.
*/ 
void moveNext(List L);
/*
*   Insert new element into L.
*   If L is non-empty, insertion takes place before front element.
*/
void prepend(List L, ListElement x);
/*
*   Insert new element into L.
*   If L is non-empty, insertion takes place after back element.
*/
void append(List L, ListElement x);
// Insert new element before cursor. Pre: length() > 0, index() >= 0
void insertBefore(List L, ListElement x);
// Insert new element after cursor. Pre: length() > 0, index() >= 0
void insertAfter(List L, ListElement x);
// Delete the front element. Pre: length() > 0
void deleteFront(List L);
// Delete the back element. Pre: length() > 0
void deleteBack(List L);
// Delete cursor element, making cursor undefined. Pre: length() > 0, index() >= 0
void delete(List L);


// Other operations ---------------------------------------------------------------------

/*
*   Prints to the file pointed to by out, a string representation of L consisting of a
*   space separated sequence of integers, with front on left.
*/
void printList(FILE* out, List L);
/*
*   Returns a new List representing the same integer sequence as L.
*   The cursor in the new list is undefined, regardless of the state of the cursor in L.
*   The state of L is unchange.
*/
List copyList(List L);


#endif
