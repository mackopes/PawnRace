//lib includes
#include <iostream>
#include <utility>

//project includes
#include "board.h"
#include "general_header.h"
#include "players/random_player.h"
#include "players/human_player.h"
#include "players/minimax_player.h"
#include "game.h"

//using
using std::cout;
using std::endl;

int main(int argc, char **argv) {
  int n_games = 1;
  if (argc > 1) {
    n_games = atoi(argv[1]);
  }
  cout << "Number of games: " << n_games << endl;
  Random_Player white_player = Random_Player(white);
  Minimax_Player black_player = Minimax_Player(black, 2000);
  int w = 0, b = 0;
  for (int i = 0; i < n_games; ++i)
  {
    cout << "Game #" << i << endl;
    Game game = Game(2, 4, &white_player, &black_player);
    game.start();
    if (game.get_winner() == black)
    {
      b++;
    } else if(game.get_winner() == white) {
      w++;
    }
  }

  cout << "White: " << w << endl;
  cout << "Black: " << b << endl;
}
