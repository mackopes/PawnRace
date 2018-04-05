#include "header_files/game_worker.h"

Game_Worker::Game_Worker(Player * white_player, Player * black_player, int n_games, int n_threads, int shift, argagg::parser_results args) {
	white_player_ = white_player;
	black_player_ = black_player;
	n_games_ = n_games;
	n_threads_ = n_threads;
	shift_ = shift;
	args_ = args;
	white_wins_ = 0;
	black_wins_ = 0;
	currently_processed_game_ = 0;
}

void Game_Worker::start() {

	Game game = Game(white_player_, black_player_);

	if (args_["no-print"]) {
		game.set_print(false);
	}

	for (int i = shift_; i < n_games_; i = i + n_threads_) {
		currently_processed_game_ = i;
		game.reset();
		game.start();
		if (game.get_winner() == black) {
			black_wins_++;
		} else if (game.get_winner() == white) {
			white_wins_++;
		}
	}

	currently_processed_game_ = -1; // mark this workes as finished
}