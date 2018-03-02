all: pawnrace

pawnrace: main.o move.o game.o random_player.o \
  human_player.o bitboard.o minimax_player.o
	g++ -Wall main.o board.o move.o utility.o game.o players/random_player.o \
	bitboard.o players/human_player.o players/minimax_player.o -o pawnrace

main.o: board.o game.o main.cpp
	g++ -c main.cpp

game.o: utility.o move.o game.cpp random_player.o board.o game.h human_player.o
	g++ -c game.cpp

random_player.o: move.o board.o bitboard.o \
  players/random_player.cpp players/random_player.h
	g++ -c players/random_player.cpp -o players/random_player.o

minimax_player.o: move.o board.o bitboard.o \
  players/minimax_player.cpp players/minimax_player.h
	g++ -c players/minimax_player.cpp -o players/minimax_player.o

human_player.o: move.o board.o bitboard.o \
  players/human_player.cpp players/human_player.h
	g++ -c players/human_player.cpp -o players/human_player.o

board.o: move.o utility.o board.cpp board.h
	g++ -c board.cpp

move.o: move.cpp move.h
	g++ -c move.cpp

bitboard.o: bitboard.cpp bitboard.h
	g++ -c bitboard.cpp

utility.o: utility.cpp utility.h
	g++ -c utility.cpp

clean:
	find . -name "*.o" -type f -delete
	rm pawnrace
