#ifndef GAME_H
#define GAME_H

//lib includes
#include <iostream>
#include <utility>
#include <vector>

//project includes
#include "general_header.h"
#include "move.h"
#include "board.h"
#include "../players/player.h"

typedef std::pair<int, int> pair_ii;

class Game {
 private:
  Board board_;
  std::vector<Move> moves_;
  Player * white_player_;
  Player * black_player_;
  Player * current_player_;
  int move_counter_;
 public:
  Game(int w, int b, Player * white_player, Player * black_player);
  Game(Player * white_player, Player * black_player);
  void start();
  bool next_move();
  tile get_winner();
};

#endif