#ifndef BENCHMARK_H
#define BENCHMARK_H

//libs includes
#include <vector>
#include <utility>
#include <sys/time.h>

//project includes
#include "../player.h"
#include "../minimax_player.h"
#include "../random_player.h"

class Benchmark_Player : public Player {
 private:
  int turn_;

  Random_Player rp;
  Minimax_Player mp;
 public:
  Benchmark_Player(tile color);
  Benchmark_Player(tile color, long max_time);
  Move get_move(Board board);
  ~Benchmark_Player();
};

#endif