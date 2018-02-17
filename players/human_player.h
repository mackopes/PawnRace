#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

//libs includes
#include <utility>
#include <algorithm>
#include <string>
#include <iostream>

//project includes
// #include "board.h"
// #include "tile.h"
// #include "move.h"
#include "player.h"
#include "../bitboard.h"
#include "../utility.h"

class Human_Player : public Player {
 private:
 public:
  Human_Player(tile color);
  Move get_move(Board board);


};

#endif