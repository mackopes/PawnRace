all: pawnrace

pawnrace: main.o move.o
	g++ -Wall main.o board.o move.o utility.o -o pawnrace

main.o: board.o main.cpp
	g++ -c main.cpp

board.o: move.o utility.o board.cpp 
	g++ -c board.cpp

move.o: move.cpp
	g++ -c move.cpp

utility.o: utility.cpp
	g++ -c utility.cpp

clean:
	rm *o
