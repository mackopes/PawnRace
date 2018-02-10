#ifndef PLAYER_H
#define PLAYER_H

//libs includes

//project includes
#include "board.h"
#include "tile.h"
#include "move.h"

class Player {
 private:
  tile color_;
 public:
  Player(tile color) {
    color_ = color;
  }

  tile color() {
    return color_;
  }

  virtual Move get_move(Board board) = 0;

};

#endif