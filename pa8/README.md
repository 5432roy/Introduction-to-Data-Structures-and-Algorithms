# CSE101 Programming Assignment 7
This project create a dictionary using BST with Red-Black structure.

## Content
| File | Description | Note |
| ----------- | ----------- | ----------- |
| Dictionary.h | Header file for the Dictionary ADT | |
| Dictionary.cpp | Implementation file for Dictionary ADT | |
| DictionaryTest.cpp | Unit test for the Dictionary ADT | |
| Order.cpp | The first main program for this project | | 
| WordFrequency.cpp | Counts the frequency of each word in input file and ouput it in alphabet order | |
| Makefile | Read the comment in Makefile | |

## Implemtation Details
- WordFrequency: since token will still contains one character `Carriage Return` with empty line, the empty line will be skip be checking the ascii value of first character in token.
