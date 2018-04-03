#ifndef PLAYER_H
#define PLAYER_H

//libs includes

//project includes
#include "../board.h"
#include "../general_header.h"
#include "../move.h"

class Player {
 private:
  tile color_;
 protected:
  bool repeat_move;
 public:
  Player(tile color) {
    color_ = color;
    repeat_move = false;
  }

  tile color() {
    return color_;
  }

  bool get_repeat() {
    return repeat_move;
  }

  virtual ~Player() {
    //empty
  }

  virtual Move get_move(Board board) = 0;
};

#endif