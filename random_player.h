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

class Random_Player : Player {
 private:
  //enum movetype {fwd, ffwd, capt, captpass}
  vector <Move> get_all_possible_moves(long long fwd_moves, long long ffwd_moves,
                                       long long capt_r_moves, long long, capt_l_moves,
                                       long long captpass_r_moves, long long captpass_l_moves);
 public:
  Move get_move(Board board);
  template<typename T>
  T get_random_element(vector<T> & v);


};

#endif