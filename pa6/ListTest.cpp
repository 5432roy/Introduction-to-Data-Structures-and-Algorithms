/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA5
 * ListTest.cpp
 * The unitTest for List ADT
*/
#include "List.h"
#include <iostream>
#include <cassert>

using namespace std;


void reportTest(const string& testName, bool result) {
    cout << testName << ": " << (result ? "PASSED" : "FAILED") << endl;
}


void check(bool condition, const string& message) {
    if (!condition) {
        reportTest(message, false);
    }
}

List setupList() {
    List myList;
    for (int i = 1; i <= 5; ++i) {
        myList.insertBefore(i);
    }
    myList.moveFront(); 
    return myList;
}

void testCopyConstructor() {
    List originalList = setupList();
    List copiedList(originalList);
    check(copiedList.equals(originalList), "CopyConstructor");
}

void testMoveFrontAndMoveBack() {
    List myList = setupList();
    myList.moveFront();
    check(myList.position() == 0, "MoveFront");

    myList.moveBack();
    check(myList.position() == myList.length(), "MoveBack");
}

void testInsertAndErase() {
    List myList;
    myList.insertAfter(1);
    check(myList.back() == 1, "InsertAfter");

    myList.insertBefore(0);
    check(myList.front() == 0, "InsertBefore");

    myList.eraseAfter();
    check(myList.length() == 1, "EraseAfter");

    myList.eraseBefore();
    check(myList.length() == 0, "EraseBefore");
}

void testFindAndCleanup() {
    List myList = setupList();
    myList.insertAfter(3); // Insert duplicate for cleanup

    int findResult = myList.findNext(3);
    check(findResult != -1, "FindNext1");

    myList.cleanup();
    findResult = myList.findNext(3);
    check(findResult == -1, "Cleanup");
}

void testToString() {
    List myList = setupList();
    string expectedString = "(1, 2, 3, 4, 5)";
    check(myList.to_string() == expectedString, "ToString");
}


void testConcat() {
    List list1 = setupList();
    List list2 = setupList();

    List concatList = list1.concat(list2);
    string expectedString = "(1, 2, 3, 4, 5, 1, 2, 3, 4, 5)";
    check(concatList.to_string() == expectedString, "ConcatToString");
    check(concatList.length() == (list1.length() + list2.length()), "ConcatLength");
}

void testPositionAndPeekMethods() {
    List myList = setupList();
    myList.moveFront();
    myList.moveNext(); // Position should now be 1

    check(myList.position() == 1, "PositionAfterMoveNext");
    check(myList.peekNext() == 2, "PeekNext");
    check(myList.peekPrev() == 1, "PeekPrev");

    myList.moveBack();
    myList.movePrev(); // Move cursor to the second last element
    check(myList.peekPrev() == 4, "PeekPrevAtBack");
}

void testSetMethods() {
    List myList = setupList();
    myList.moveFront();
    myList.moveNext(); // Cursor is now at 1, next element is 2
    myList.setAfter(20);
    check(myList.peekNext() == 20, "SetAfter");

    myList.setBefore(10);
    myList.movePrev(); // Cursor should now be at the element before 10
    check(myList.peekNext() == 10, "SetBefore");
}

void testMoveNextPrevMethods() {
    List myList = setupList();
    myList.moveFront();
    ListElement passedOver = myList.moveNext(); // Should be 1
    check(passedOver == 1 && myList.position() == 1, "MoveNext");

    passedOver = myList.movePrev(); // Should go back to 0
    check(passedOver == 1 && myList.position() == 0, "MovePrev");
}

void testFindNextPrev() {
    List myList = setupList();
    myList.insertAfter(3); // Duplicate element for the find operation

    int position = myList.findNext(3);
    check(position == 1, "FindNext2");

    myList.moveBack();
    position = myList.findPrev(3);
    check(position == 3, "FindPrev2");
}

void testClearAndEmptyState() {
    List myList = setupList();
    myList.clear();
    check(myList.length() == 0 && myList.position() == 0, "ClearAndEmptyState");
}

void testEqualsOperator() {
    List listA = setupList();
    List listB = setupList();
    check(listA.equals(listB), "EqualsOperator");

    listB.moveFront(); // Alter listB cursor
    check(listA.equals(listB), "EqualsOperatorWithDifferentCursor");
}

void testAssignmentOperator() {
    List listA = setupList();
    List listB;
    listB = listA; // Test assignment operator
    check(listB.equals(listA), "AssignmentOperator");
}



int main() {
    testCopyConstructor();
    testMoveFrontAndMoveBack();
    testInsertAndErase();
    testFindAndCleanup();
    testToString();
    testConcat();
    testPositionAndPeekMethods();
    testSetMethods();
    testMoveNextPrevMethods();
    testFindNextPrev();
    testClearAndEmptyState();
    testEqualsOperator();
    testAssignmentOperator();
    
    cout << "All tests completed." << endl;

    return 0;
}
