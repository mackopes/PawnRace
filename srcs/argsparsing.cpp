#include "header_files/argsparsing.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

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
