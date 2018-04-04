#include "header_files/game.h"
#include "header_files/utility.h"

Game::Game(int w, int b, Player * white_player, Player * black_player) {
  board_ = Board(w, b);
  black_player_ = black_player;
  white_player_ = white_player;
  current_player_ = white_player_;
  move_counter_ = 0;
}

Game::Game(Player * white_player, Player * black_player) {
  board_ = Board();
  black_player_ = black_player;
  white_player_ = white_player;
  current_player_ = white_player_;
  move_counter_ = 0;
}


void Game::start() {
  while (next_move())
    continue;

  std::cout << board_ << std::endl;

  switch (board_.won()) {
  case none:
    std::cout << "Draw" << std::endl;
    break;
  case black:
    std::cout << "Black won" << std::endl;
    break;
  case white:
    std::cout << "White won" << std::endl;
    break;
  default:
    std::cout << "unknown winner" << std::endl;
    break;
  }
}

bool Game::next_move() {
  if (board_.won() == none) {
    //print board
    std::cout << board_ << std::endl;
    // print player

    Move move = current_player_ -> get_move(board_);
    if (current_player_ -> get_repeat()) {
      while (!board_.apply_move(move)) {
        if (move.is_no_move()) {
          std::cout << "No more moves" << std::endl;
          return false;
        }
        move = current_player_ -> get_move(board_);
      }
    } else {
      if (!board_.apply_move(move)) {
        if (!move.is_no_move()) {
          std::cerr << move << std:: endl;
          std::cerr << "Move unsuccessfull" << std::endl;
        } else {
          std::cout << "No more moves" << std::endl;
        }
        return false;
      }
    }
    //std::cout << (current_player_ -> color() == white ? "White" : "Black") << "'s turn" << std::endl;
    //std::cout << move << std::endl;


    //switch player
    current_player_ = current_player_ == white_player_ ? black_player_ : white_player_;

    return true;
  } else {
    return false;
  }
}

tile Game::get_winner() {
  return board_.won();
}
