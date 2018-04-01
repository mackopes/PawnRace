//lib includes
#include <iostream>
#include <utility>
#include <algorithm>
#include <string>

//project includes
#include "board.h"
#include "general_header.h"
#include "players/random_player.h"
#include "players/human_player.h"
#include "players/minimax_player.h"
#include "game.h"
#include "utility.h"
#include "dllibs/argagg.hpp"

//using
using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main(int argc, char **argv) {
  //more to come
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
      }
    }};

  argagg::parser_results args;
  try {
    args = argparser.parse(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  if (args["help"]) {
    std::cerr << argparser;
    return EXIT_SUCCESS;
  }

  //get number of games
  int n_games = 1;
  if (args["ngames"]) {
    n_games = args["ngames"];
  }

  cout << "macka" << endl;
  //initialize players
  Player * white_player;
  if (args["white"]) {
    string whitearg = string_to_lower(args["white"]);
    if (string("human").compare(whitearg) == 0) {
      Human_Player tmp_p = Human_Player(white);
      white_player = &tmp_p;
      cout << "White Player: Human" << endl;
    } else if (string("random").compare(whitearg) == 0) {
      Random_Player tmp_p = Random_Player(white);
      white_player = &tmp_p;
      cout << "White Player: Random" << endl;
    } else if (string("ai").compare(whitearg) == 0) {
      int t = 5000;
      if (args["aitimeout"]) {
        t = args["aitimeout"];
      }
      Minimax_Player tmp_p = Minimax_Player(white, t);
      white_player = &tmp_p;
      cout << "White Player: AI" << endl;
    } else {
      cerr << "Unkown player type." << endl;
      return 0;
    }
  } else {
    int t = 5000;
    if (args["aitimeout"]) {
      t = args["aitimeout"];
    }
    Minimax_Player tmp_p = Minimax_Player(white, t);
    white_player = &tmp_p;
    cout << "White Player: AI" << endl;
  }

  Player * black_player;
  if (args["black"]) {
    string blackarg = string_to_lower(args["black"]);
    if (string("human").compare(blackarg) == 0) {
      Human_Player tmp_p = Human_Player(black);
      black_player = &tmp_p;
      cout << "Black Player: Human" << endl;
    } else if (string("random").compare(blackarg) == 0) {
      Random_Player tmp_p = Random_Player(black);
      black_player = &tmp_p;
      cout << "Black Player: Random" << endl;
    } else if (string("ai").compare(blackarg) == 0) {
      int t = 5000;
      if (args["aitimeout"]) {
        t = args["aitimeout"];
      }
      Minimax_Player tmp_p = Minimax_Player(black, t);
      black_player = &tmp_p;
      cout << "Black Player: AI" << endl;
    } else {
      cerr << "Unkown player type." << endl;
      return 0;
    }
  } else {
    int t = 5000;
    if (args["aitimeout"]) {
      t = args["aitimeout"];
    }
    Minimax_Player tmp_p = Minimax_Player(black, t);
    black_player = &tmp_p;
    cout << "Black Player: AI" << endl;
  }

  cout << "Number of games: " << n_games << endl;
  int w = 0, b = 0;
  for (int i = 1; i <= n_games; ++i) {
    cout << "Game #" << i << endl;
    Game game = Game(white_player, black_player);
    game.start();
    if (game.get_winner() == black) {
      b++;
    } else if (game.get_winner() == white) {
      w++;
    }
  }

  cout << "White: " << w << endl;
  cout << "Black: " << b << endl;
}
