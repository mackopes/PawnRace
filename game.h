#ifndef GAME_H
#define GAME_H

//lib includes
#include <iostream>
#include <utility>
#include <vector>

//project includes
#include "general_header.h"
#include "game.h"
#include "tile.h"
#include "utility.h"
#include "move.h"

typedef std::pair<int, int> pair_ii;

class Game {
  //players
  Board board_;
  vector<Move> moves;


};

#endif