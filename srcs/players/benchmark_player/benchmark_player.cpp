#include "benchmark_player.h"

#define MINRAND 1
#define MAXRAND 6
#define PROB_AF_THRESHOLD 0.92

Benchmark_Player :: Benchmark_Player(tile color) : Player(color) {
  rp = new Random_Player(color);
  mp = new Minimax_Player(color);
  turn_ = 0;

  timeval t1;
  gettimeofday(&t1, NULL);
  srand(t1.tv_usec * t1.tv_sec);
}

Benchmark_Player :: Benchmark_Player(tile color, long max_time) : Player(color) {
  rp = new Random_Player(color);
  mp = new Minimax_Player(color, max_time);
  turn_ = 0;

  timeval t1;
  gettimeofday(&t1, NULL);
  srand(t1.tv_usec * t1.tv_sec);
}

int Benchmark_Player :: random_int(int min, int max) {
  return ((rand() % (max - min + 1)) + min);
}

Move Benchmark_Player :: get_move(Board board) {
  turn_++;

  if (turn_ >= MAXRAND) {
    if (random_int(0, 1000) > PROB_AF_THRESHOLD * 1000) {
      return rp -> get_move(board);
    } else {
      return mp -> get_move(board);
    }
  }

  if (random_int(MINRAND, MAXRAND) >= turn_) {
    return rp -> get_move(board);
  } else {
    return mp -> get_move(board);
  }
}

Benchmark_Player :: ~Benchmark_Player() {
  delete rp;
  delete mp;
}