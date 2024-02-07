#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 4
#
#  make                     makes Sparse
#  make MatrixTest          makes MatrixTest
#  make ListTest            makes ListTest
#  make all					makes all executable
#  make clean               removes all binaries
#  make SparseCheck         runs Sparse in valgrind on in5
#  make MatrixCheck         runs MatrixTest in valgrind
#  make ListCheck           runs ListTest in valgrind
#------------------------------------------------------------------------------

BASE_SOURCES	= Matrix.c List.c
BASE_OBJECTS	= Matrix.o List.o
HEADERS			= Matrix.h List.h
EXE				= Sparse MatrixTest ListTest
COMPILE        	= gcc -std=c17 -Wall -c
LINK           	= gcc -std=c17 -Wall -o
REMOVE			= rm -f
MEMCHECK       	= valgrind --leak-check=full

Sparse: Sparse.o $(BASE_OBJECTS)
	$(LINK) Sparse Sparse.o $(BASE_OBJECTS)

Sparse.o: Sparse.c $(HEADERS)
	$(COMPILE) Sparse.c

MatrixTest: MatrixTest.o $(BASE_OBJECTS)
	$(LINK) MatrixTest MatrixTest.o $(BASE_OBJECTS)

MatrixTest.o: MatrixTest.c $(HEADERS)
	$(COMPILE) MatrixTest.c

ListTest: ListTest.o List.o
	$(LINK) ListTest ListTest.o List.o

ListTest.o: ListTest.c List.h
	$(COMPILE) ListTest.c

all: $(EXE)

$(BASE_OBJECTS): $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean:
	$(REMOVE) *.o
	$(REMOVE) $(EXE)

SparseCheck: Sparse
	$(MEMCHECK) ./Sparse in5 out5

ListCheck: ListTest
	$(MEMCHECK) ./ListTest

MatrixCheck: MatrixTest
	$(MEMCHECK) ./MatrixTest




