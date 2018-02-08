#include "bitboard.h"

long long bitshift(int i, int j) {
  return (1L << (i * 8 + j));
}

void getll(long long & white, long long & black, long long & en_pass, Board board) {
  white = black = en_pass = 0;

  for (int i = 0; i < BOARDSIZE; ++i) {
    for (int j = 0; j < BOARDSIZE; ++j) {
      if (board.is_white(i, j)) {
        white |= bitshift(i, j);
      } else if (board.is_black(i, j)) {
        black |= bitshift(i, j);
      } else if (board.is_en_pass(i, j)) {
        en_pass |= bitshift(i, j);
      }
    }
  }
}