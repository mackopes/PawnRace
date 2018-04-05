//lib includes
#include <iostream>
#include <utility>
#include <algorithm>
#include <string>

//project includes
#include "header_files/board.h"
#include "header_files/general_header.h"
#include "players/random_player/random_player.h"
#include "players/human_player/human_player.h"
#include "players/minimax_player/minimax_player.h"
#include "players/benchmark_player/benchmark_player.h"
#include "header_files/game.h"
#include "header_files/utility.h"
#include "../dllibs/argagg.hpp"

//using
using namespace std;

argagg::parser_results get_args(int argc, char **argv) {
  argagg::parser argparser {{
      {
        "help", {"-h", "--help"},
        "shows this help message", 0
      },
      {
        "white", {"-w", "--white"},
        "Set white player. Types of player: Human, Random, AI(default)", 1
      },
      {
        "black", {"-b", "--black"},
        "Set black player. Types of player: Human, Random, AI(default)", 1
      },
      {
        "ngames", {"-n", "--ngames"},
        "Set number of games to play. Default: 1", 1
      },
      {
        "aitimeout", {"--ai-timeout"},
        "Set timoeut of AIs. Default: 5000", 1
      },
      {
        "benchmark", {"--benchmark"},
        "Benchmark two players against each other", 0
      },
      {
        "no-print", {"--no-print"},
        "Disables printing of board after each move", 0
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
      } else if (string("black").compare(player) == 0) {
        ret = new Human_Player(black);
      }

      if (string("white").compare(player) == 0) {
        cout << "White Player: Human" << endl;
      } else if (string("black").compare(player) == 0) {
        cout << "Black Player: Human" << endl;
      }

    } else if (string("random").compare(playerarg) == 0) {
      if (string("white").compare(player) == 0) {
        ret = new Random_Player(white);
      } else if (string("black").compare(player) == 0) {
        ret = new Random_Player(black);
      }

      if (string("white").compare(player) == 0) {
        cout << "White Player: Random" << endl;
      } else if (string("black").compare(player) == 0) {
        cout << "Black Player: Random" << endl;
      }

    } else if (string("ai").compare(playerarg) == 0) {
      int t = 5000;

      if (args["aitimeout"]) {
        t = args["aitimeout"];
      }

      if (string("white").compare(player) == 0) {
        ret = new Minimax_Player(white, t);
      } else if (string("black").compare(player) == 0) {
        ret = new Minimax_Player(black, t);
      }

      if (string("white").compare(player) == 0) {
        cout << "White Player: AI" << endl;
      } else if (string("black").compare(player) == 0) {
        cout << "Black Player: AI" << endl;
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
      cout << "White Player: AI" << endl;
    } else if (string("black").compare(player) == 0) {
      cout << "Black Player: AI" << endl;
    }

    if (string("white").compare(player) == 0) {
      cout << "White Player: AI" << endl;
    } else if (string("black").compare(player) == 0) {
      cout << "Black Player: AI" << endl;
    }

  }

  if (args["benchmark"]) {
    ret = new Benchmark_Player(ret);
  }

  return ret;
}


int main(int argc, char **argv) {
  argagg::parser_results args = get_args(argc, argv);

  //get number of games
  int n_games = 1;
  if (args["ngames"]) {
    n_games = args["ngames"];
  }

  //initialize players
  Player * white_player = get_player(args, "white");
  Player * black_player = get_player(args, "black");

  cout << "Number of games: " << n_games << endl;
  int w = 0, b = 0;
  for (int i = 1; i <= n_games; ++i) {
    cout << "Game #" << i << endl;
    Game game = Game(white_player, black_player);
    if (args["no-print"]) {
      game.set_print(false);
    }
    game.reset();
    game.start();
    if (game.get_winner() == black) {
      b++;
    } else if (game.get_winner() == white) {
      w++;
    }
  }

  delete white_player;
  delete black_player;

  cout << "White: " << w << endl;
  cout << "Black: " << b << endl;
}
