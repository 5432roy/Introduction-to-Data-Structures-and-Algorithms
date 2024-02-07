/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA5
 * Shuffle.cpp
 * The main program for this project.
 * This program will do a riffle shuffle on a List, where List is the ADT defined in "List.h",
 * and determine how many shuffles are necessary to bring a List back into its original order.
*/
#include<iostream>
#include<iomanip>
#include<string>
#include"List.h"

using namespace std;

#define MAX_LEN 300;


void shuffle(List& L) {
    List front;
    List back;
    int index = 0, length = L.length();

    L.moveFront();

    while(index < length / 2) {
        front.insertBefore(L.moveNext());
        index += 1;
    }

    while(index < length) {
        back.insertBefore(L.moveNext());
        index += 1;
    }

    front.moveFront();
    back.moveFront();
    L.clear();

    while(front.position() < front.length() || back.position() < back.length()) {
        if(front.position() < front.length() && back.position() < back.length() ) {
            L.insertBefore(back.moveNext());
            L.insertBefore(front.moveNext());
            continue;
        }

        if(front.position() < front.length()) {
            L.insertBefore(front.moveNext());
        }

        if(back.position() < back.length()) {
            L.insertBefore(back.moveNext());
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cerr << "Usage: ./Shffule <integer>" << endl;
        return EXIT_FAILURE;
    }

    int size = atoi(argv[1]);
    if(size <= 0) {
        cerr << "Size has to be a natrual number (>0)" << endl;
    }

    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    List L, shuffled;
    for(int i = 0; i < size; i++) {
        L.insertBefore(i);
        shuffled.insertBefore(i);

        int count = 1;
        shuffle(shuffled);

        while(!(shuffled == L)) {
            shuffle(shuffled);
            count += 1;
        }
        cout << " " << i + 1 << std::setw(16) << count << endl;
    }

    return EXIT_SUCCESS;
}
