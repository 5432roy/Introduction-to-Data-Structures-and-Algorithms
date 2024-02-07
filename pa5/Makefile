#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListClient     make ListClient
#  make ListTest	   make ListTest
#  make clean          removes binary files
#  make check1         runs valgrind on Shuffle with CLA 35
#  make check2         runs valgrind on ListClient
#  make check3		   runs valgrind on ListTest
#------------------------------------------------------------------------------

EXE					= Shuffle ListTest ListClient
CC					= g++
CFLAGS				= -std=c++17 -Wall

Shuffle : Shuffle.o List.o
	$(CC) $(CFLAGS) -o Shuffle Shuffle.o List.o 

Shuffle.o : List.h Shuffle.cpp
	$(CC) $(CFLAGS) -c Shuffle.cpp

ListClient : ListClient.o List.o
	$(CC) $(CFLAGS) -o ListClient ListClient.o List.o 

ListClient.o : List.h ListClient.cpp
	$(CC) $(CFLAGS) -c ListClient.cpp

ListTest: ListTest.o List.o
	$(CC) $(CFLAGS) -o ListTest ListTest.o List.o

ListTest.o: List.h ListTest.cpp
	$(CC) $(CFLAGS) -c ListTest.cpp

List.o : List.h List.cpp
	$(CC) $(CFLAGS) -c List.cpp

clean :
	rm -f *.o $(EXE)

check2 : ListClient
	valgrind --leak-check=full ListClient

check1 : Shuffle
	valgrind --leak-check=full Shuffle 35

check3 : ListTest
	valgrind --leak-check=full ListTest