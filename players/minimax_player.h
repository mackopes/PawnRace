#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

//libs includes
#include <vector>
#include <utility>
#include <sys/time.h>
#include <limits>
#include <cmath>
#include <ctime>

//project includes
// #include "board.h"
// #include "tile.h"
// #include "move.h"
#include "player.h"
#include "../bitboard.h"
#include "../utility.h"

#define ll unsigned long long
#define DBLMIN std::numeric_limits<double>::lowest()
#define DBLMAX std::numeric_limits<double>::max()

class Minimax_Player : public Player {
 private:
  long max_time_;
  std::clock_t start_time_;
  bool timeout_flag_;

  Move minimax(ll attacker, ll deffender, ll ep);
  double alphabeta_maximizing(ll attacker, ll deffender, ll ep, int cur_depth, int max_depth, double alpha, double beta);
  double alphabeta_minimizing(ll attacker, ll deffender, ll ep, int cur_depth, int max_depth, double alpha, double beta);
  Move minimax_start(ll attacker, ll deffender, ll ep, int max_depth);
  double eval(ll attacker, ll deffender, int depth);
  double eval_positions(ll attacker, ll deffender);
  void set_timer();
  bool timeout();
 public:
  Minimax_Player(tile color);
  Minimax_Player(tile color, long max_time);
  Move get_move(Board board);
};

#endif