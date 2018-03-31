#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

//libs includes
#include <vector>
#include <utility>
#include <sys/time.h>
#include <limits>

//project includes
// #include "board.h"
// #include "tile.h"
// #include "move.h"
#include "player.h"
#include "../bitboard.h"
#include "../utility.h"

#define ll unsigned long long
#define DBLMIN std::numeric_limits<double>::lowest()
#define DBLMAX std::numeric_limits<double>::max();

class Minimax_Player : public Player {
 private:
  double minimax(ll attacker, ll deffender, ll ep, double alpha, double beta, Move & best_move, int current_depth, int max_depth, double carry);
  double minimax_helper(ll attacker, ll deffender, ll ep, double alpha, double beta, ll & best_move, int current_depth, int max_depth, double carry, movetype mov);
  double eval(ll attacker, ll deffender);
 public:
  Minimax_Player(tile color);
  Move get_move(Board board);
};

#endif