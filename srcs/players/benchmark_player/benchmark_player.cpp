#include "benchmark_player.h"

Benchmark_Player :: Benchmark_Player(tile color) : Player(color) {
    rp = new Random_Player(color);
    mp = new Minimax_Player(color);
    turn_ = 0;
}

Benchmark_Player :: Benchmark_Player(tile color, long max_time) : Player(color) {
    rp = new Random_Player(color);
    mp = new Minimax_Player(color, max_time);
    turn_ = 0;
}

Move Benchmark_Player :: get_move(Board board) {
    return Move();
}

Benchmark_Player :: ~Benchmark_Player() {
    delete rp;
    delete mp;
}