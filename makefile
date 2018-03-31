CC=g++ -std=c++14
FLAGS=-Wall
PLAYERS=random_player.cpp human_player.cpp minimax_player.cpp
SOURCES=main.cpp move.cpp game.cpp bitboard.cpp board.cpp utility.cpp \
        $(addprefix player/,$(PLAYERS))
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTALBE=pawnrace

all: pawnrace

pawnrace: main.o move.o game.o players/random_player.o \
  players/human_player.o bitboard.o players/minimax_player.o
	$(CC) $(FLAGS) main.o board.o move.o utility.o game.o players/random_player.o \
	bitboard.o players/human_player.o players/minimax_player.o -o pawnrace

main.o: board.o game.o main.cpp
	$(CC) -c main.cpp

game.o: utility.o move.o game.cpp players/random_player.o board.o game.h \
  players/human_player.o players/minimax_player.o
	$(CC) -c game.cpp

players/random_player.o: move.o board.o bitboard.o \
  players/random_player.cpp players/random_player.h
	$(CC) -c players/random_player.cpp -o players/random_player.o

players/minimax_player.o: move.o board.o bitboard.o \
  players/minimax_player.cpp players/minimax_player.h
	$(CC) -c players/minimax_player.cpp -o players/minimax_player.o

players/human_player.o: move.o board.o bitboard.o \
  players/human_player.cpp players/human_player.h
	$(CC) -c players/human_player.cpp -o players/human_player.o

board.o: move.o utility.o board.cpp board.h
	$(CC) -c board.cpp

move.o: move.cpp move.h
	$(CC) -c move.cpp

bitboard.o: bitboard.cpp bitboard.h
	$(CC) -c bitboard.cpp

utility.o: utility.cpp utility.h
	$(CC) -c utility.cpp

clean:
	find . -name "*.o" -type f -delete
	rm pawnrace
