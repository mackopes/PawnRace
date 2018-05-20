#include "benchmark_player.h"

#define RANDMOVES 2

Benchmark_Player :: Benchmark_Player(Player * benchmarked_player) : Player(benchmarked_player -> color()) {
  //exception if inserted wrong player

  rp = new Random_Player(benchmarked_player -> color());
  bp = benchmarked_player;
  turn_ = 0;
}

Move Benchmark_Player :: get_move(Board board) {
  turn_++;
  if (turn_ <= RANDMOVES) {
    return rp -> get_move(board);
  } else {
    return bp -> get_move(board);
  }

}

Benchmark_Player :: ~Benchmark_Player() {
  delete rp;
  delete bp;
}

void Benchmark_Player::reset() {
  rp -> reset();
  bp -> reset();
}
