#include "game.h"

Game::Game(int w, int b, Player white_player, Player black_player) {
  board_ = Board(w, b);
  black_player_ = black_player;
  current_player_ = white_player_ = white_player;
  move_counter_ = 0;
}

Game::Game(Player white_player, Player black_player) {
  boad_ = Board();
  black_player_ = black_player;
  current_player_ = white_player_ = white_player;
  move_counter_ = 0;
}


void start() {
  while (next_move())
    continue;

  switch (board_.won()) {
  case none:
    cout << "Draw" << endl;
    break;
  case black:
    cout << "Black won" << endl;
    break;
  case white:
    cout << "White won" << endl;
    break;
  default:
    cout << "unknown winner" << endl;
    break;
  }
}

bool next_move() {
  if (board_.won() == none) {

    //print board
    cout << board << endl;
    // print player


    Move move = current_player_.get_move(board_);
    if (!board_.apply_move(move)) {
      cerr << "Move unsuccessfull" << endl;
      //print move
      return false;
    }

    //switch player
    current_player_ = current_player_ == white_player_ ? black_player_ : white_player_;

    return true;
  } else {
    return false;
  }
}
