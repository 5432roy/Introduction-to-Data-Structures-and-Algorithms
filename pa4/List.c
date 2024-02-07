/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA4
*   List.c 
*   Implementation file for List ADT
*****************************************************************************************/
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"


// structs ------------------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {
   ListElement data;
   Node next;
   Node previous;
} NodeObj;

// private ListObj type
typedef struct ListObj {
   Node front;
   Node cursor;
   Node back;
   int index;
   int length;
} ListObj;

// Constructors-Destructors -------------------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next, prev and data fields.
Node newNode(ListElement data) {
   Node N = malloc(sizeof(NodeObj));
   assert(N != NULL);

   N->data = data;
   N->next = NULL;
   N->previous = NULL;

   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) {
   if(pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList() {
   List l;
   l = malloc(sizeof(ListObj));
   assert(l != NULL);

   l->front = l->back = l->cursor = NULL;
   l->length = 0;
   l->index = -1;

   return (l);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL) {
   clear(*pL);
   free(*pL);
   *pL = NULL;
}


// Helper functions ---------------------------------------------------------------------

// Check if the L is NULL, if so, print the error message and exit.
void checkListExistence(List L, char* function) {
    if(L == NULL) {
        printf("%s: NULL List reference\n", function);
        exit(EXIT_FAILURE);
    }
}

// Check if length() > 0. Pre: L != NULL
void checkListLength(List L, char* function) {
    if(L->length <= 0) {
        printf("%s: Accessing empty List\n", function);
        exit(EXIT_FAILURE);
    }
}

// Check if index() >= 0. Pre: L != NULL, length() > 0 
void checkListIndex(List L, char* function) {
    if(L->index < 0) {
        printf("%s: Accessing List with invalid cursor \n", function);
        exit(EXIT_FAILURE);
    }
}


// Access functions ---------------------------------------------------------------------

int length(List L) {
    checkListExistence(L, "length");

    return (L->length);
}

int index(List L) {
    checkListExistence(L, "index");

    return (L->index);
}

ListElement front(List L) {
    checkListExistence(L, "front");
    checkListLength(L, "front");

    return (L->front->data);
}

ListElement back(List L) {
    checkListExistence(L, "back");
    checkListLength(L, "back");

    return (L->back->data);
}

ListElement get(List L) {
    checkListExistence(L, "get");
    checkListLength(L, "get");
    checkListIndex(L, "get");

    return (L->cursor->data);
}


// Manipulation procedures ----------------------------------------------------

void clear(List L) {
   while(length(L) != 0) {
      deleteFront(L);
   }
}

void set(List L, ListElement x) {
    checkListExistence(L, "set");
    checkListLength(L, "set");
    checkListIndex(L, "set");

    L->cursor->data = x;
}

void moveFront(List L) {
    checkListExistence(L, "moveFront");

    if(length(L) > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L) {
    checkListExistence(L, "moveBack");

    if(length(L) > 0) {
        L->cursor = L->back;
        L->index = length(L) - 1;
    }
}

void movePrev(List L) {
    checkListExistence(L, "movePrev");

    if(L->cursor == NULL) {
        return;
    }

    if(L->cursor == L->front) {
        L->cursor = NULL;
        L->index = -1;
        return;
    }
    
    L->cursor = L->cursor->previous;
    L->index -= 1;
}

void moveNext(List L) {
    checkListExistence(L, "moveNext");

    if(L->cursor == NULL) {
        return;
    }

    if(L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
        return;
    }

    L->cursor = L->cursor->next;
    L->index += 1;
}

void prepend(List L, ListElement x) {
    checkListExistence(L, "prepend");

    Node N = newNode(x);

    if(length(L) > 0) {
        N->next = L->front;
        L->front->previous = N;
        L->front = N;
        if(L->cursor != NULL) {
            L->index += 1;
        }
    }

    if(length(L) == 0) {
        L->front = N;
        L->back = N;
    }

    L->length += 1;
}

void append(List L, ListElement x) {
    checkListExistence(L, "append");

    Node N = newNode(x);

    if(length(L) > 0) {
        N->previous = L->back;
        L->back->next = N;
        L->back = N;
    }

    if(length(L) == 0) {
        L->front = N;
        L->back = N;
    }

    L->length += 1;
}

void insertBefore(List L, ListElement x) {
    checkListExistence(L, "insertBefore");
    checkListLength(L, "insertBefore");
    checkListIndex(L, "insertBefore");

    if(L->cursor == L->front) {
        prepend(L, x);
        return;
    }

    Node N = newNode(x);
    N->previous = L->cursor->previous;
    N->next = L->cursor;
    L->cursor->previous->next = N;
    L->cursor->previous = N;

    L->length += 1;
    L->index += 1;
}

void insertAfter(List L, ListElement x) {
    checkListExistence(L, "insertAfter");
    checkListLength(L, "insertAfter");
    checkListIndex(L, "insertAfter");

    if(L->cursor == L->back) {
        append(L, x);
        return;
    }

    Node N = newNode(x);
    N->previous = L->cursor;
    N->next = L->cursor->next;
    L->cursor->next->previous = N;
    L->cursor->next = N;

    L->length += 1;
}

void deleteFront(List L) {
    checkListExistence(L, "deleteFront");
    checkListLength(L, "deleteFront");

    // restore the status of list
    if(length(L) == 1) {
        freeNode(&(L->front));
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
        L->length = 0;
        return;
    }

    // free the front node and make front.next "new front"
    L->front = L->front->next;
    freeNode(&(L->front->previous));
    L->front->previous = NULL;

    L->index -= 1;
    L->length -= 1;

    // if index < 0, cursor set to NULL and set index to -1 again (otherwise if keeps removing front could have index < -1)
    if(L->index < 0) {
        L->index = -1;
        L->cursor = NULL;
    }

}

void deleteBack(List L) {
    checkListExistence(L, "deleteBack");
    checkListLength(L, "deleteBack");

    // restore the status of list
    if(length(L) == 1) {
        freeNode(&(L->front));
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
        L->length = 0;
        return;
    }

    L->back = L->back->previous;
    freeNode(&(L->back->next));
    L->back->next = NULL;
    
    L->length -= 1;

    if(L->index == L->length) {
        L->index = -1;
        L->cursor = NULL;
    }
}

void delete(List L) {
    checkListExistence(L, "delete");
    checkListLength(L, "delete");
    checkListIndex(L, "delete");

    if(length(L) == 1 || L->cursor == L->front) {
        deleteFront(L);
        return;
    }

    if(L->cursor == L->back) {
        deleteBack(L);
        return;
    }

    L->cursor->previous->next = L->cursor->next;
    L->cursor->next->previous = L->cursor->previous;

    freeNode(&(L->cursor));
    L->cursor = NULL;
    L->index = -1;
    L->length -= 1;
}
