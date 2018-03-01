#ifndef MINIMAXPLAYER_H
#define MINIMAXLAYER_H

//libs includes
#include <vector>
#include <utility>
#include <sys/time.h>

//project includes
// #include "board.h"
// #include "tile.h"
// #include "move.h"
#include "player.h"
#include "../bitboard.h"
#include "../utility.h"

class Minimax_Player : public Player {
 private:
  //
 public:
  Minimax_Player(tile color);
  Move get_move(Board board);


};

#endif