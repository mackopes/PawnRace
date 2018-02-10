//lib includes
#include <iostream>
#include <utility>

//project includes
#include "board.h"
#include "general_header.h"
#include "random_player.h"
#include "game.h"

//using
using std::cout;
using std::endl;

int main() {
  /*Board b(4, 7);

  cout << b << endl;
  cout << endl;

  b.apply_move(Move(white, std::make_pair(6, 2), std::make_pair(4, 2), false, true));
  cout << b << endl;

  b.apply_move(Move(black, std::make_pair(1, 5), std::make_pair(2, 5), false, false));
  cout << b << endl;*/

  Random_Player white_player = Random_Player();
  Random_Player black_player = Random_Player();
  Game game = Game(white_player, black_player);
  game.start();
}