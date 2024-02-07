/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA6
 * List.cpp
 * Implementation of the List ADT
*/
#include<iostream>
#include<string>
#include<stdexcept>
#include <bits/stdc++.h>
#include"List.h"

/*** Private Constructor ***/

// Node costructor
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}


/*** Class Constructors & Destructors ***/

List::List() {
    frontDummy = new Node((ListElement)INT_MAX);
    backDummy = new Node((ListElement)INT_MAX);

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = frontDummy;
    afterCursor = backDummy;

    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L) {
    frontDummy = new Node((ListElement)INT_MAX);
    backDummy = new Node((ListElement)INT_MAX);

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = frontDummy;
    afterCursor = backDummy;

    pos_cursor = 0;
    num_elements = 0;

    Node* runner = L.backDummy->prev;
    while(runner != L.frontDummy) {
        insertAfter(runner->data);
        runner = runner->prev;        
    }
}

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}


/*** Access functions ***/

int List::length() const {
    return num_elements;
}

ListElement List::front() const {
    if(length() <= 0) {
        throw std::length_error("List: front(): empty List\n");
    }

    return frontDummy->next->data;
}

ListElement List::back() const {
    if(length() <= 0) {
        throw std::length_error("List: back(): empty List\n");
    }

    return backDummy->prev->data;
}

int List::position() const {
    return pos_cursor;
}

ListElement List::peekNext() const {
    if(position() >= length()) {
        throw std::range_error("List: peekNext(): at the end of the List\n");
    }
    
    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if(position() <= 0) {
        throw std::range_error("List: peekPrev(): at the head of the List\n");
    }
    
    return beforeCursor->data;
}


/*** Manipulation procedures ***/

void List::clear() {
    moveFront();
    while(num_elements > 0) {
        eraseAfter();
    }
}

void List::moveFront() {
    pos_cursor = 0;
    afterCursor = frontDummy->next;
    beforeCursor = frontDummy;
}

void List::moveBack() {
    pos_cursor = length();
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

ListElement List::moveNext() {
    if(position() >= length()) {
        throw std::range_error("List: moveNext(): at the end of the List\n");
    }

    afterCursor = afterCursor->next;
    beforeCursor = beforeCursor->next;
    pos_cursor += 1;

    return beforeCursor->data;
}

ListElement List::movePrev() {
    if(position() <= 0) {
        throw std::range_error("List: movePrev(): at the head of the List\n");
    }
    
    afterCursor = afterCursor->prev;
    beforeCursor = beforeCursor->prev;
    pos_cursor -= 1;

    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    Node* new_node = new Node(x);
    
    new_node->next = afterCursor;
    new_node->prev = beforeCursor;

    afterCursor->prev = new_node;
    beforeCursor->next = new_node;

    afterCursor = new_node;

    num_elements += 1;
}

void List::insertBefore(ListElement x) {
    Node* new_node = new Node(x);

    new_node->next = afterCursor;
    new_node->prev = beforeCursor;

    afterCursor->prev = new_node;
    beforeCursor->next = new_node;

    beforeCursor = new_node;

    num_elements += 1;
    pos_cursor += 1;
}

void List::setAfter(ListElement x) {
    if(position() >= length()) {
        throw std::range_error("List: setAfter(): at the end of the List\n");
    }

    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if(position() <= 0) {
        throw std::range_error("List: setBefore(): at the head of the List\n");
    }

    beforeCursor->data = x;
}

void List::eraseAfter() {
    if(position() >= length()) {
        throw std::range_error("List: eraseAfter(): at the end of the List\n");
    }

    Node* temp = afterCursor;

    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;

    afterCursor = afterCursor->next;

    delete temp;
    num_elements -= 1;
}

void List::eraseBefore() {
    if(position() <= 0) {
        throw std::range_error("List eraseBefore: at the head of the List\n");
    }

    Node* temp = beforeCursor;

    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;

    beforeCursor = afterCursor->prev;

    delete temp;
    num_elements -= 1;
    pos_cursor -= 1;
}


/*** Other Functions ***/

int List::findNext(ListElement x) {
    while (position() < length()){
        if (moveNext() == x){
            return position();
        }
    }

    return -1;
}

int List::findPrev(ListElement x) {
    while (position() > 0){
        if (movePrev() == x){
            return position();
        }
    }

    return -1;
}

void List::cleanup() {
    List seen;
    Node* node = frontDummy->next;
    int count = 0;
    bool found_cursor = false;

    while(node != backDummy) {
        found_cursor |= node == afterCursor;
        seen.moveFront();
        if(seen.findNext(node->data) == -1) {
            seen.insertAfter(node->data);
            count += found_cursor ? 0 : 1;
        }
        node = node->next;
    }

    clear();

    seen.moveFront();

    while(seen.position() < seen.length()) {
        insertBefore(seen.moveNext());
    }

    moveFront();

    for(int i = 0; i < count; i++) {
        moveNext();
    }
}

List List::concat(const List& L) const {
    List concat_L(L);

    Node* r1 = frontDummy->next;

    concat_L.moveFront();

    while(r1 != backDummy) {
        concat_L.insertBefore(r1->data);
        r1 = r1->next;
    }

    concat_L.moveFront();

    return concat_L;
}

std::string List::to_string() const {
    Node* runner = frontDummy->next;

    std::string str = "(";

    while(runner != backDummy) {
        str += std::to_string(runner->data);
        runner = runner->next;
        if(runner != backDummy) {
            str += ", ";
        }
    }

    str += ")";

    return str;
}

bool List::equals(const List& R) const {
    if(length() != R.length()) {
        return false;
    }

    Node* N1 = frontDummy;
    Node* N2 = R.frontDummy;

    while(N1->next != backDummy && N2->next != R.backDummy) {
        if(N1->data != N2->data) {
            return false;
        }
        N1 = N1->next;
        N2 = N2->next;
    }

    return true;
}

/*** Overriden Operators ***/

std::ostream& operator<<(std::ostream& stream, const List& L) {
    return stream << L.to_string();
}

bool operator==(const List& A, const List& B) {
    return A.equals(B);
}

List& List::operator=(const List& L) {
    if (this != &L){
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }

    return *this;
}