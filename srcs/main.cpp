//lib includes
#include <iostream>
#include <utility>
#include <algorithm>
#include <string>
#include <thread>
#include <chrono>

//project includes
#include "header_files/board.h"
#include "header_files/general_header.h"
#include "players/player.h"
#include "header_files/game.h"
#include "header_files/utility.h"
#include "header_files/game_worker.h"
#include "../dllibs/argagg.hpp"
#include "header_files/argsparsing.h"

#define DEF_THREADS 1

//using
using namespace std;


void thread_task(Game_Worker * p) {
  p -> start();
}

int main(int argc, char **argv) {
  argagg::parser_results args = get_args(argc, argv);

  //get number of games
  int n_games = 1;
  if (args["ngames"]) {
    n_games = args["ngames"];
  }

  cout << "Number of games: " << n_games << endl;
  int w = 0, b = 0;

  int n_threads = thread::hardware_concurrency() < DEF_THREADS ? thread::hardware_concurrency() : DEF_THREADS;
  if (args["n-threads"]) {
    n_threads = args["n-threads"];
  }
  cout << "Using " << n_threads << " threads" << endl;

  vector<Game_Worker *> workers;
  workers.resize(n_threads);
  vector<thread> worker_threads;

  for (int i = 0; i < n_threads; ++i) {
    //Game_worker(Player* white_player, Player* black_player, int n_games, int n_threads, int shift, argagg::parser_results args)
    workers[i] = new Game_Worker(get_player(args, "white"), get_player(args, "black"), n_games, n_threads, i, args);
    worker_threads.emplace_back(thread_task, workers[i]);
    this_thread::sleep_for(chrono::milliseconds(20));
  }

  double last_progress = -1;
  while (true) {
    int min_game = n_games + 1;
    for (int i = 0; i < n_threads; ++i) {
      if ((workers[i]->get_curr_processed_game() != -1) && (workers[i]->get_curr_processed_game() < min_game)) {
        min_game = workers[i]->get_curr_processed_game();
      }
    }
    if (min_game == n_games + 1) {
      break; //all finished
    } else {
      double progress = double(min_game) / double(n_games);
      if (progress > last_progress) {
        cout << progress * 100 << "%" << endl;
        last_progress = progress;
      }
    }
    this_thread::sleep_for(chrono::milliseconds(200));
  }

  for (int i = 0; i < n_threads; ++i) {
    worker_threads[i].join();
    b += workers[i]->get_black_wins();
    w += workers[i]->get_white_wins();
    delete workers[i];
  }

  cout << "White: " << w << " (" << double(w) / double(n_games) * 100 << "%)" << endl;
  cout << "Black: " << b << " (" << double(b) / double(n_games) * 100 << "%)" << endl;
}
