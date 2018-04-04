#ifndef BENCHMARK_H
#define BENCHMARK_H

//libs includes
#include <vector>
#include <utility>
#include <sys/time.h>
#include <random>

//project includes
#include "../../header_files/move.h"
#include "../player.h"
#include "../minimax_player/minimax_player.h"
#include "../random_player/random_player.h"

class Benchmark_Player : public Player {
 private:
  int turn_;

  Random_Player * rp;
  Minimax_Player * mp;

  int random_int(int min, int max);
 public:
  Benchmark_Player(tile color);
  Benchmark_Player(tile color, long max_time);
  Move get_move(Board board);
  ~Benchmark_Player();
};

#endif