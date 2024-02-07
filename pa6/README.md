# CSE101 Programming Assignment 6
This project uses the [List ADT](https://git.ucsc.edu/cse101/fall23/schan88/-/blob/pa5/pa5/README.md?ref_type=heads) from assgiment 5 to build a class `BigInteger`.
`BigInteger` can hold large number of Integer beyond the bond of `int` or `long`.

## Content
| File | Description | Note |
| ----------- | ----------- | ----------- |
| List.h | Header file for List ADT | | 
| List.cpp | Implementation file for List ADT | Unlike PA5 the `ListElement` is now `long`|
| ListTest.cpp | Unit Tests for List ADT | Since only `ListElement` is changed, the old test case from PA5 should work the same|
| BigInteger.h | Header file for BigInteger ADT | | 
| BigInteger.cpp | Implementation file for BigInteger ADT | |
| BigIntegerTest.cpp | Unit Tests for BigInteger ADT | |
| Arithemetic.cpp | the client program to perfrom basic arithmetic operation with BigInteger | |
| Makefile   | Read the comment in Makefile | |


## Implementation Details
Although there are some helper functions mentioned in the PDF, I think this program can also work perfectly with the helper functions.

- `BigInteger BigInteger::add(const BigInteger& N) const`: This function basically handle both ***add*** or ***subtract*** by utlizing `negate()` properly.
- `BigInteger BigInteger::sub(const BigInteger& N) const`: This function simply calls `add()` with negated `N`
- `std::string BigInteger::to_string()`: ***#include \<sstream\>*** and ***#include \<iomanip\>*** to fill the *0s*, it is also possible to use a for loop to do the same thing, but this way is more elegant.
