all: pawnrace

pawnrace: main.o move.o game.o randomplayer.o bitboard.o
	g++ -Wall main.o board.o move.o utility.o game.o random_player.o 
	bitboard.o -o pawnrace

main.o: board.o game.o main.cpp
	g++ -c main.cpp

game.o: utility.o move.o game.cpp randomplayer.o
	g++ -c game.cpp

randomplayer.o: move.o board.o bitboard.o random_player.cpp
	g++ -c random_player.cpp

board.o: move.o utility.o board.cpp 
	g++ -c board.cpp

move.o: move.cpp
	g++ -c move.cpp

bitboard.o:
	g++ -c bitboard.cpp

utility.o: utility.cpp
	g++ -c utility.cpp

clean:
	rm *.o
