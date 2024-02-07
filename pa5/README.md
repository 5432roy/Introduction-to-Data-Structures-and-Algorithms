# CSE101 Programming Assignment 5
This project is to build a List ADT in C++, and implement it to perform riffle shuffle on a List.

## Content
| File | Description | Note |
| ----------- | ----------- | ----------- |
| List.h | Header file for List ADT | | 
| List.cpp | Implementation file for List ADT | |
| ListTest.cpp | Unit Tests for List ADT | |
| Shuffle.cpp    | Main program for this project | Usage: `./Shuffle <number>` number will be the length of the list|
| Makefile   | Read the comment in Makefile | |


## Implementation Details
- `cleanup()`: This function used an auxiliary `List` to serve as a `Set`. It only adds the value that haven't contained in it. After having the `Set`, `clear()` the original `List` and add this unique value from `Set` to it. There is a integer `count` that keep track of the cursor of the original `List` by knowing how many unique value are in front of the cursor. By this implementation, the `Node` will not be the same `Node` as the `List` before `cleanup()`, but only having the same property.
