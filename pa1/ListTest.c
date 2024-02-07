/****************************************************************************************
*   Shang-Yu Chan
*   schan88
*   2023 Fall CSE101 PA1
*   ListClient.c
*   Test client for List ADT
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){

   // Constructors-Destructors -------------------------------------------------------------
   
   // List newList();
   List A = newList();
   
   // void freeList(List* pL);
   freeList(&A);


   // Access functions ---------------------------------------------------------------------
   
   A = newList();

   // int length(List L); 

   // expecting 0
   printf("%d ", length(A));

   // int index(List L); 

   // expecting -1
   printf("%d ", index(A));

   // Add two items to test the following
   append(A, 0);
   append(A, 1);

   // ListElement front(List L);  

   // expecting 0
   printf(FORMAT, front(A));

   // ListElement back(List L);

   // expecting 1
   printf(FORMAT, back(A));

   // ListElement get(List L);

   // moveFront to test the cursor
   moveFront(A);

   // expecting 0
   printf(FORMAT, get(A));

   // bool equals(List A, List B);
   // expecting false and then true
   List B = newList();

   printf("%d", equals(A, B));

   append(B, 0);
   append(B, 1);

   printf("%d", equals(A, B));

   printf("\nManipulation procedures: \n");

   freeList(&B);


   // Manipulation procedures --------------------------------------------------------------

   // void clear(List L); 
   // expecting 0, -1, 2
   clear(A);


   // 0 -1
   printf("%d ", length(A));
   printf("%d ", index(A));

   append(A, 2);

   // 2
   printf(FORMAT, front(A));

   // void set(List L, ListElement x);
   moveFront(A);
   set(A, 3);

   // void moveFront(List L)
   moveFront(A);

   // expecting 3
   printf(FORMAT, front(A));

   append(A, 4);

   // void movBack(List L);
   moveBack(A);

   // A >> 3 , "4"

   // expecting 4
   printf(FORMAT, get(A));

   
   // void movePrev(List L);
   movePrev(A);

   // A >> "3" , 4

   // expecting 3
   printf(FORMAT, get(A));

   // void moveNext(List L);
   moveNext(A);

   // A >> 3 , "4"
   
   // expecting 4
   printf(FORMAT, get(A));

   
   // void prepend(List L, ListElement x);
   prepend(A, 5);

   // A >> 5 , 3 , "4"

   // expecting 5
   printf(FORMAT, front(A));

   // void append(List L, ListElement x); >> already used

   // void insertBefore(List L, ListElement x);
   moveFront(A);
   moveNext(A);

   // A >> 5 , "3" , 4

   insertBefore(A, 6);

   // A >> 5 , 6 , "3" , 4

   // expecting 3
   printf(FORMAT, get(A));

   movePrev(A);

   // A >> 5 , "6" , 3 , 4

   // expecting 6
   printf(FORMAT, get(A));

   movePrev(A);

   // A >> "5" , 6 , 3 , 4

   // expecting 5
   printf(FORMAT, get(A));


   // void insertAfter(List L, ListElement x);
   insertAfter(A, 7);

   // expecting 5
   printf(FORMAT, get(A));

   moveNext(A);

   // A >> 5 , "7" , 6 , 3 , 4

   // expecting 7
   printf(FORMAT, get(A));

   // void deleteFront(List L);
   deleteFront(A);

   // expecting 7
   printf(FORMAT, front(A));

   // void deleteBack(List L);
   deleteBack(A);

   // expecting 3
   printf(FORMAT, back(A));

   // void delete(List L);
   moveNext(A);

   delete(A);

   // expecting -1
   printf(FORMAT, index(A));

   moveFront(A);
   moveNext(A);

   // A >>  7 , "3"

   // expecing 3
   printf(FORMAT, get(A));

   printf("\nOther operations: \n");

   // Other operations ---------------------------------------------------------------------

   // void printList(FILE* out, List L); tested by other file

   // List copyList(List L);

   B = copyList(A);

   // -1
   printf("%d ", index(B));

   moveFront(B);

   // 7
   printf(FORMAT, get(B));

   moveNext(B);

   // 3
   printf(FORMAT, get(B));

   freeList(&A);
   freeList(&B);

   printf("\nEverything works just fine! \n");

   return(0);
}
