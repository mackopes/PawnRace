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
#include "players/random_player/random_player.h"
#include "players/human_player/human_player.h"
#include "players/minimax_player/minimax_player.h"
#include "players/benchmark_player/benchmark_player.h"
#include "header_files/game.h"
#include "header_files/utility.h"
#include "header_files/game_worker.h"
#include "../dllibs/argagg.hpp"

#define DEF_THREADS 1

//using
using namespace std;

argagg::parser_results get_args(int argc, char **argv) {
  argagg::parser argparser {{
      {
        "help", {"-h", "--help"},
        "Show this help message.", 0
      },
      {
        "white", {"-w", "--white"},
        "Set white player. Types of player: Human, Random, AI(default).", 1
      },
      {
        "black", {"-b", "--black"},
        "Set black player. Types of player: Human, Random, AI(default).", 1
      },
      {
        "ngames", {"-n", "--ngames"},
        "Set number of games to play. Default: 1.", 1
      },
      {
        "aitimeout", {"--ai-timeout"},
        "Set timoeut of AIs. Default: 5000.", 1
      },
      {
        "benchmark", {"--benchmark"},
        "Benchmark two players against each other.", 0
      },
      {
        "no-print", {"--no-print"},
        "Disables printing of board after each move.", 0
      },
      {
        "n-threads", {"--n-threads"},
        "Number of threads to use. Default: 1.", 1
      },
      {
        "switch-sides", {"-s", "--switch-sides"},
        "Switch starting player every second game.", 0
      }
    }};

  argagg::parser_results args;
  try {
    args = argparser.parse(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  if (args["help"]) {
    std::cerr << argparser;
    exit(EXIT_SUCCESS);
  }

  return args;
}

Player * get_player(argagg::parser_results args, string player) {
  Player * ret;
  if (args[player]) {
    string playerarg = string_to_lower(args[player]);
    if (string("human").compare(playerarg) == 0) {
      if (string("white").compare(player) == 0) {
        ret = new Human_Player(white);
        if (!args["no-print"]) {
          cout << "White Player: Human" << endl;
        }
      } else if (string("black").compare(player) == 0) {
        ret = new Human_Player(black);
        if (!args["no-print"]) {
          cout << "Black Player: Human" << endl;
        }
      }

    } else if (string("random").compare(playerarg) == 0) {
      if (string("white").compare(player) == 0) {
        ret = new Random_Player(white);
        if (!args["no-print"]) {
          cout << "White Player: Random" << endl;
        }
      } else if (string("black").compare(player) == 0) {
        ret = new Random_Player(black);
        if (!args["no-print"]) {
          cout << "Black Player: Random" << endl;
        }
      }

    } else if (string("ai").compare(playerarg) == 0) {
      int t = 5000;

      if (args["aitimeout"]) {
        t = args["aitimeout"];
      }

      if (string("white").compare(player) == 0) {
        ret = new Minimax_Player(white, t);
        if (!args["no-print"]) {
          cout << "White Player: AI" << endl;
        }
      } else if (string("black").compare(player) == 0) {
        ret = new Minimax_Player(black, t);
        if (!args["no-print"]) {
          cout << "Black Player: AI" << endl;
        }
      }

    } else {
      cerr << "Unkown player type." << endl;
      exit(0);
    }
  } else {
    int t = 5000;

    if (args["aitimeout"]) {
      t = args["aitimeout"];
    }

    if (string("white").compare(player) == 0) {
      ret = new Minimax_Player(white, t);
      if (!args["no-print"]) {
        cout << "White Player: AI" << endl;
      }
    } else if (string("black").compare(player) == 0) {
      ret = new Minimax_Player(black, t);
      if (!args["no-print"]) {
        cout << "Black Player: AI" << endl;
      }
    }

  }

  if (args["benchmark"]) {
    ret = new Benchmark_Player(ret);
  }

  return ret;
}

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
