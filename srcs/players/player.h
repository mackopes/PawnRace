#ifndef PLAYER_H
#define PLAYER_H

//libs includes

//project includes
#include "../header_files/board.h"
#include "../header_files/general_header.h"
#include "../header_files/move.h"

class Player {
 private:
  tile color_;
  bool print_;
 protected:
  bool repeat_move;
 public:
  Player(tile color) {
    color_ = color;
    repeat_move = false;
    print_ = false;
  }

  virtual void set_print(bool print) {
    print_ = print;
  }

  bool get_print() {
    return print_;
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

  /* Resets player to original state before starting new game
   * Should be implemented in derived classes in case player
   * behaves differently based on previous turns
   */
  virtual void reset() {
    //empty
  }

  virtual Move get_move(Board board) = 0;
};

#endif
