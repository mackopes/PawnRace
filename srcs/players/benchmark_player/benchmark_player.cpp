#include "benchmark_player.h

Benchmark_Player :: Benchmark_Player(tile color) : Player(color) {
	rp = Random_Player(color);
	mp = Minimax_Player(color);
	turn_ = 0;
}

Benchmark_Player :: Benchmark_Player(tile color, long max_time) : Player(color) {
	rp = Random_Player(color);
	mp = Minimax_Player(color, max_time);
	turn_ = 0;
}

Benchmark_Player :: Move get_move(Board board) {
}

Benchmark_Player :: ~Benchmark_Player() {
	//empty
}