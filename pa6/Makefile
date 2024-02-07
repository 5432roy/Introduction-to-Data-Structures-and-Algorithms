#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 6
#
#  make                     makes Arithmetic
#  make BigIntegerTest    	makes BigIntegerTest
#  make ListTest          	makes ListTest
#  make clean               removes all binaries
#  make ArithmeticCheck     runs Arithmetic in valgrind on in4 junk4
#  make BigIntegerCheck     runs BigIntegerTest in valgrind
#  make ListCheck           runs ListTest in valgrind
#------------------------------------------------------------------------------

COMPILE			= g++ -std=c++17 -Wall -c
LINK			= g++ -std=c++17 -Wall -o
REMOVE			= rm -f
MEMCHECK		= valgrind --leak-check=full
EXE				= Arithmetic BigIntegerTest ListTest BigIntegerTest ListTest

Arithmetic: Arithmetic.o BigInteger.o List.o
	$(LINK) Arithmetic Arithmetic.o BigInteger.o List.o

BigIntegerTest: BigIntegerTest.o BigInteger.o List.o
	$(LINK) BigIntegerTest BigIntegerTest.o BigInteger.o List.o

ListTest: ListTest.o List.o
	$(LINK) ListTest ListTest.o List.o

Arithmetic.o: Arithmetic.cpp BigInteger.h List.H
	$(COMPILE) Arithmetic.cpp

BigIntegerTest.o: BigIntegerTest.cpp BigInteger.h List.H
	$(COMPILE) BigIntegerTest.cpp

ListTest.o: ListTest.cpp List.H
	$(COMPILE) ListTest.cpp

BigInteger.o: BigInteger.cpp BigInteger.h
	$(COMPILE) BigInteger.cpp

List.o: List.cpp List.H
	$(COMPILE) List.cpp

clean:
	$(REMOVE) $(EXE)
	$(REMOVE) *.o

ArithmeticCheck: Arithmetic
	$(MEMCHECK) Arithmetic in4 junk4

BigIntegerCheck: BigIntegerTest
	$(MEMCHECK) BigIntegerTest

ListCheck: ListTest
	$(MEMCHECK) ListTest