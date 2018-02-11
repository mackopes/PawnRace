//lib includes
#include <iostream>
#include <string>
//project includes
#include "board.h"
#include "utility.h"

//using
using std::cout;
using std::endl;
using std::string;

Board::Board() {
  for (int i = 0; i < BOARDSIZE; ++i) {
    for (int j = 0; j < BOARDSIZE; ++j) {
      if (i == 1) {
        tiles_[i][j] = black;
      } else if (i == BOARDSIZE - 2) {
        tiles_[i][j] = white;
      } else {
        tiles_[i][j] = none;
      }
    }
  }
}

Board::Board(int w, int b) : Board() {
  tiles_[BOARDSIZE - 2][w - 1] = none;
  tiles_[1][b - 1] = none;
}

std::ostream& operator<< (std::ostream &out, Board const& board) {
  string alphabet = "   A B C D E F G H   ";
  cout << alphabet << endl;

  for (int i = 0; i < BOARDSIZE; ++i) {
    cout << BOARDSIZE - i << "  ";
    for (int j =  0; j < BOARDSIZE; ++j) {
      if (board.is_black(i, j)) {
        cout << BLACKPAWN;
      } else if (board.is_white(i, j)) {
        cout << WHITEPAWN;
      } else if (board.is_empty(i, j)) {
        cout << '.';
      } else if (board.is_en_pass(i, j)) {
        cout << 'x';
      } else {
        cout << ' ';
      }
      cout << ' ';
    }
    cout << " " << BOARDSIZE - i << endl;
  }

  cout << alphabet << endl;

  return out;
}

tile Board::won() const {
  if (number_of_pawns(black) == 0 && number_of_pawns(white) > 0) {
    return white;
  }

  if (number_of_pawns(black) > 0 && number_of_pawns(white) == 0) {
    return black;
  }

  return none;
}

int Board::number_of_pawns(tile p) const {
  int sum = 0;
  for (int i = 0; i < BOARDSIZE; ++i) {
    for (int j = 0; j < BOARDSIZE; ++j) {
      sum = tiles_[i][j] == p ? sum + 1 : sum;
    }
  }

  return sum;
}

bool Board::apply_move(Move move) {
  if (!is_valid_move(move)) {
    return false;
  }

  pair_ii from = move.get_from();
  pair_ii to = move.get_to();

  for (int i = 0; i < BOARDSIZE; ++i) {
    tiles_[BLACKROW + BLACKDIR][i]
      = tiles_[BLACKROW + BLACKDIR][i] == en_pass ?
        none
        : tiles_[BLACKROW + BLACKDIR][i];
    tiles_[WHITEROW + WHITEDIR][i]
      = tiles_[WHITEROW + WHITEDIR][i] == en_pass ?
        none
        : tiles_[WHITEROW + WHITEDIR][i];
  }
  if (move.is_capture() && move.is_en_passant()) {
    tiles_[to.first][to.second] = tiles_[from.first][to.second];
    tiles_[from.first][from.second] = none;
    tiles_[from.first][to.second] = none;
  } else {
    tiles_[to.first][to.second] = tiles_[from.first][to.second];
    tiles_[from.first][from.second] = none;
    if (move.is_en_passant()) {
      tiles_[(to.first + from.first) / 2][to.second] = en_pass;
    }
  }

  return true;
}

bool Board::is_valid_move(Move move) {
  pair_ii from = move.get_from();
  pair_ii to = move.get_to();
  tile player = move.get_player();

  std::cout << "from " << from.first << ' ' << from.second << " to " << to.first << ' ' << to.second << std::endl;
  int direction = player == black ? BLACKDIR : WHITEDIR;
  if (!move.is_capture() && !move.is_en_passant()) {       // normal fwd move
    return ((from.second == to.second)
            && (from.first + direction == to.first)
            && (tiles_[from.first][from.second] == player)
            && (tiles_[to.first][to.second] == none)
           );
  } else if (!move.is_capture() && move.is_en_passant()) {     //double fwd move
    return ((from.second == to.second)
            && (from.first + 2 * direction == to.first)
            && (tiles_[from.first][from.second] == player)
            && (tiles_[to.first][to.second] == none)
            && (tiles_[from.first + direction][from.second] == none)
           );
  } else if (move.is_capture() && !move.is_en_passant()) {   //capture, no en_pass
    return ((abs(from.second - to.second) == 1)
            && (from.first + direction == to.first)
            && (tiles_[from.first][from.second] == player)
            && (tiles_[to.first][to.second] == get_opposite_player(player))
           );
  } else if (move.is_capture() && move.is_en_passant()) {   //capture , en_pass
    return ((abs(from.second - to.second) == 1)
            && (from.first + direction == to.first)
            && (tiles_[from.first][from.second] == player)
            && (tiles_[to.first][to.second] == en_pass)
            && (tiles_[from.first][to.second] == get_opposite_player(player))
           );
  }
}