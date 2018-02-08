#ifndef MOVE_H
#define MOVE_H

//lib includes
#include <iostream>
#include <utility>

//project includes
#include "general_header.h"
#include "tile.h"

typedef std::pair<int, int> pair_ii;

class Move {
 private:
  tile player_;
  pair_ii from_;
  pair_ii to_;
  bool capture_;
  bool en_passant_;
 public:
  Move(tile player, pair_ii from, pair_ii to, bool capture, bool en_passant);
  bool is_capture() const { return capture_; }
  bool is_en_passant() const { return en_passant_; }
  pair_ii get_from() const { return from_; }
  pair_ii get_to() const { return to_; }
  tile get_player() const { return player_; }
};



#endif