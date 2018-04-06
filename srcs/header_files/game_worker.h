#ifndef GAME_WORKER_H
#define GAME_WORKER_H

#include <iostream>

#include "../players/player.h"
#include "game.h"
#include "../../dllibs/argagg.hpp"

class Game_Worker {
 private:
	Player* white_player_;
	Player* black_player_;
	int n_games_;
	int n_threads_;
	int shift_;
	argagg::parser_results args_;
	int white_wins_;
	int black_wins_;
	int currently_processed_game_;

 public:
	Game_Worker(Player * white_player, Player * black_player, int n_games, int n_threads, int shift, argagg::parser_results args);
	void start();
	int get_white_wins() {
		return white_wins_;
	}
	int get_black_wins() {
		return black_wins_;
	}

	/* return currently processed game.
	 * return 0 if no games have been processed yet
	 * return -1 if all games have been processed
	 */
	int get_curr_processed_game() {
		return currently_processed_game_;
	}
	~Game_Worker() {
		delete white_player_;
		delete black_player_;
	}
};


#endif