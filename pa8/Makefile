#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT_TEST       = $(ADT)Test
ADT_Client     = $(ADT)Client
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(MAIN).o $(ADT_OBJECT)
	$(LINK) $(MAIN) $(MAIN).o $(ADT_OBJECT)

$(MAIN).o: $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

Order: Order.o $(ADT_OBJECT)
	$(LINK) Order Order.o $(ADT_OBJECT)

Order.o: Order.cpp $(ADT_HEADER)
	$(COMPILE) Order.cpp

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)
	
$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_Client): $(ADT_Client).o $(ADT_OBJECT)
	$(LINK) $(ADT_Client) $(ADT_Client).o $(ADT_OBJECT)
	
$(ADT_Client).o: $(ADT_Client).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_Client).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(ADT_TEST) *.o $(ADT_Client) Order 

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)
