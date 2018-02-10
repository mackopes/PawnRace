#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

//libs includes
#include <vector>
#include <random>
#include <utility>

//project includes
#include "board.h"
#include "tile.h"
#include "move.h"
#include "player.h"
#include "random_player.h"
#include "bitboard.h"

class Random_Player : public Player {
 private:
  //enum movetype {fwd, ffwd, capt, captpass}
  std::vector <Move> get_all_possible_moves(std::vector<long long> move_ll);
  template<typename T>
  T random_element(std::vector<T> & v);
 public:
  Random_Player(tile color);
  Move get_move(Board board);


};

#endif